/*
 * Aplicacion.h
 *
 *  Created on: 14/06/2013
 *      Author: Marcelo
 */

#ifndef APLICACION_H_
#define APLICACION_H_

	#include "FW_Display-Expansion2.h"
	#include "FW_GPIO.h"
	#include "KitInfo2_BaseBoard.h"
	#include "Oscilador.h"
	#include "RegsLPC1769.h"
	#include "Teclado_4x1.h"

	#define T0 1 // Prendo led ROJO Llevo el timpo de barrido al valor normal de 2,5 mseg
	#define T1 2 // Prendo led AZUL apago ROJO
	#define T2 3 // Prendo led VERDE apago AZUL
	#define T3 4 // Apago todos
	#define T4 5 // Prendo todos Aumento barrido a 10 mseg para mostrar el efecto en el display

	#define	RGB_RED_ON		SetPIN(RGBR,ON)
	#define	RGB_RED_OFF		SetPIN(RGBR,OFF)
	#define	RGB_BLUE_ON		SetPIN(RGBB,ON)
	#define	RGB_BLUE_OFF	SetPIN(RGBB,OFF)
	#define	RGB_GREEN_ON	SetPIN(RGBG,ON)
	#define	RGB_GREEN_OFF	SetPIN(RGBG,OFF)

	void InicializarKit ( void );
	uint8_t Teclado( void );

#endif /* APLICACION_H_ */
