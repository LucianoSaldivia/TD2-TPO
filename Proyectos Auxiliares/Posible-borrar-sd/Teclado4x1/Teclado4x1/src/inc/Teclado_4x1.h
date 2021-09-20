/*
 * Teclado_4x1.h
 *
 *  Created on: 30/09/2013
 *      Author: marcelo
 */

#ifndef TECLADO_4X1_H_
#define TECLADO_4X1_H_

	#include "Aplicacion.h"

	#define     SW1_OFF     GetPIN(KEY0,ACTIVO_BAJO)
    #define     SW4_OFF     GetPIN(KEY1,ACTIVO_BAJO)
    #define     SW7_OFF     GetPIN(KEY2,ACTIVO_BAJO)
    #define     SW10_OFF    GetPIN(KEY3_RC,ACTIVO_BAJO)
    #define     SW13_OFF    GetPIN(KEY4_RC,ACTIVO_BAJO)

	#define 	CANT_REBOTES	10 //valor empírico
	#define		REPOSO			0
	#define		DETECCION		1
	#define		CHEQUEO			2
	#define		EMERGENCIA		CHEQUEO
	#define		NO_KEY			(uint8_t) 0xFF

	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */
	void DriverTeclado(void);
	void TecladoSW (uint8_t);
	uint8_t TecladoHW (void);


#endif /* TECLADO_4X1_H_ */
