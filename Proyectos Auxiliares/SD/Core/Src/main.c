/*
 * Ejemplo de lectura y escritura de archivos en una memoria SD.
 * Conecto la SD al SPI1 del STM32F103C8 en los pines:
 * A4 -> SD_CS
 * A5 -> SD_SCLK
 * A6 -> SD_MISO (Línea con Pull-up) de 4k7
 * A7 -> SD_MOSI
 * C4 -> SD_PRESENT
 *
 * El código está basado en el de http://elm-chan.org/fsw/ff/ffsample.zip
 * Sólo que tuve que inicializar la SD en modo 3 para que el código funcione
 * El código ocupa unos 25Kb de flash usando las funciones de strings de la
 * biblioteca Fat_fs. http://elm-chan.org/fsw/ff/00index_e.html.
 *
 * El funcionamiento del programa es el siguiente:
 * 	- 	Lee del archivo en el raíz "config.txt" y la primer línea intenta
 * 		convertirla en un número en ms y lo usa como ton y toff del led de
 * 		la placa.
 *
 * 	-	Escribe la salida de HAL_GetTick() y lo anexa en formato texto
 * 		en el archivo del raíz de la SD "datos.txt"
 *
 */

#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer_monitor.h"
#include "ff.h"
#include "diskio.h"

#define TICKS_SISTEMA	(1)
#define TICKS_SD		(1000)
#define TICKS_LEDS		(50)

uint32_t ticks;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
uint32_t get_fattime(void);

int main(void)
{
	uint32_t t_us;
	uint32_t ticks_sd_write;
	uint32_t ticks_leds;
	uint32_t bw;
	int ton;
	int len;
	char datos[64];
	FATFS fs;
	FIL fp;
	FILINFO fno;
	FRESULT res;

	HAL_Init();

	ticks = TICKS_SISTEMA;
	ticks_leds = TICKS_LEDS;
	ticks_sd_write = TICKS_SD;
	SystemClock_Config();
	MX_GPIO_Init();
	inic_timer();

	start_timer();
	f_mount(&fs, "", 0);
	res = f_open(&fp, "0:config.txt", FA_OPEN_EXISTING | FA_READ);
	t_us = stop_timer();
	/*
	 * La primera vez, que incluye inicializar la SD,
	 * montar la SD y abrir el archivo tarda 14,8ms
	 *
	 */

	ton = TICKS_LEDS;
	if (res == FR_OK)
	{
		start_timer();
		f_gets(datos, 64, &fp);
		f_close(&fp);
		t_us = stop_timer();
		ton = atoi(datos);
	}
	ticks_leds = ton;
	/*
	 * La lectura de un string del archivo config.txt
	 * tarda 1,95ms
	 *
	 */

	start_timer();
	f_open(&fp, "0:datos.txt", FA_OPEN_ALWAYS | FA_WRITE);
	f_stat("0:datos.txt", &fno);
	f_lseek(&fp, fno.fsize);
	f_sync(&fp);
	t_us = stop_timer();
	/*
	 * Abrir el archivo para escribir y moverme al final
	 * de este tarda unos 3,3ms (Ya inicializó la SD)
	 */

	while (1)
	{
		if (!ticks)
		{
			ticks = TICKS_SISTEMA;
			if (!--ticks_leds)
			{
				ticks_leds = ton;
				ticks_leds = ton;
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			}

			if (!--ticks_sd_write)
			{
				ticks_sd_write = TICKS_SD;
				sprintf(datos, "%d\r\n", (int) HAL_GetTick());
				len = strlen(datos);
				start_timer();
				f_write(&fp, (const void*) datos, len, (UINT*) &bw);
				f_sync(&fp);
				t_us = stop_timer();
				/*
				 * Hacer un log en la SD en el archivo datos.txt
				 * tarda unos 7,5ms
				 */
			}
			UNUSED(t_us);
		}
	}
}

/*
 * Función requerida por la biblioteca de código
 */
uint32_t get_fattime(void)
{
	uint32_t dia = 8;
	uint32_t mes = 7;
	uint32_t anio = 2020;
	return ((anio - 1980) << 25) | (mes << 21) | (dia << 16);
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

	/*Configure GPIO pin : PC13 */
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}
