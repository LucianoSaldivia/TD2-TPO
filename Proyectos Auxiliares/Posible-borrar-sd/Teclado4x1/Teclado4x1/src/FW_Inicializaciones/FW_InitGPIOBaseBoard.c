#include "Aplicacion.h"

	//1°)Selecciono FUNCION del pin en PINSELx.
	//void SetPINSEL (uint8_t puerto, uint8_t pin, uint8_t modo)

	//2°)A aquellos pines configurados como GPIO, les configuro su DIRECCION en FIOxDIR
	//void SetDIR(registro* puerto,uint8_t pin,uint8_t direccion)
	//ENTRADA = 0 - SALIDA = 1

	//3°) SI son ENTRADAS, debe definirse su configuración eléctrica
	// void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
	//!< 00	Pull Up resistor enable (reset value)		01	repeated mode enable
	//!< 11	Pull Down resistor enable					10	ni Pull Up ni Pull DOwn

void Inicializar_Teclado( void )
{
	SetPINSEL ( KEY0 , PINSEL_GPIO);
	SetPINSEL ( KEY1 , PINSEL_GPIO);
	SetPINSEL ( KEY2 , PINSEL_GPIO);
	SetPINSEL ( KEY3_RC , PINSEL_GPIO);
	SetPINSEL ( KEY4_RC , PINSEL_GPIO);

	SetDIR ( KEY0 , ENTRADA);
	SetDIR ( KEY1 , ENTRADA);
	SetDIR ( KEY2 , ENTRADA);
	SetDIR ( KEY3_RC , ENTRADA);
	SetDIR ( KEY4_RC , ENTRADA);

	SetPINMODE ( KEY0 , PINMODE_PULLUP);
	SetPINMODE ( KEY1 , PINMODE_PULLUP);
	SetPINMODE ( KEY2 , PINMODE_PULLUP);
}

void Inicializar_Relay( void )
{
	SetPINSEL ( LED1 , PINSEL_GPIO);
	SetPINSEL ( LED2 , PINSEL_GPIO);
	SetPINSEL ( LED3 , PINSEL_GPIO);
	SetPINSEL ( LED4 , PINSEL_GPIO);
	SetPINSEL ( BUZZ , PINSEL_GPIO);

	SetDIR ( LED1 , SALIDA);
	SetDIR ( LED2 , SALIDA);
	SetDIR ( LED3 , SALIDA);
	SetDIR ( LED4 , SALIDA);
	SetDIR ( BUZZ , SALIDA);

	SetPIN (BUZZ, BUZZ_OFF);  //se apaga con 1
}

void Inicializar_RGB( void )
{
	SetPINSEL ( RGBR , PINSEL_GPIO);
	SetPINSEL ( RGBG , PINSEL_GPIO);
	SetPINSEL ( RGBB , PINSEL_GPIO);

	SetDIR ( RGBR , SALIDA);
	SetDIR ( RGBG , SALIDA);
	SetDIR ( RGBB , SALIDA);
}

