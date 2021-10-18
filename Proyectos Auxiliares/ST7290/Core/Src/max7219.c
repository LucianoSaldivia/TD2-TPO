#include "stm32f1xx_hal.h"
#include <stdint.h>

static SPI_HandleTypeDef *spi_handler;
static GPIO_TypeDef *gpio_cs;
static uint16_t pin_cs;

static void comando(uint32_t address, uint32_t data)
{
	uint16_t datoSerie;
	datoSerie = ((address & 0x0F) << 8) | (data & 0xFF);
	HAL_GPIO_WritePin(gpio_cs, pin_cs, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi_handler, (void*) &datoSerie, 1, 10);
	HAL_GPIO_WritePin(gpio_cs, pin_cs, GPIO_PIN_SET);
}

void llenar_max7219(uint8_t dato)
{
	int i;
	for (i = 0; i < 8; i++)
		comando(i + 1, dato);
}

void dibujar_max7219(uint8_t *datos)
{
	int i;
	for (i = 0; i < 8; i++)
		comando(i + 1, datos[i]);
}

void inicializar_max7219(SPI_HandleTypeDef *spi, GPIO_TypeDef *GPIO_cs,
		uint16_t GPIO_Pin_cs)
{
	spi_handler = spi;
	gpio_cs = GPIO_cs;
	pin_cs = GPIO_Pin_cs;

	comando(0x0C, 0x01);	//Enciendo
	comando(0x0F, 0x00);	//Salgo de modoTest
	comando(0x09, 0x00);	//Sin decodificar
	comando(0x0B, 0x07);	//Muestro todas las lineas.
	comando(0x0A, 0x0F);	//Intensidad
	llenar_max7219(0x00);	//Borro la pantalla.

}
