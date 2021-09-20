/*
 * KitInic.c
 */

#include "Aplicacion.h"

//-----------------------------------------------------------------------------
// Configuración del SysTick para 10ms
//-----------------------------------------------------------------------------
void InicSysTick(void){ //si divido x 4, interrumpe cada 2,5ms
		STRELOAD  = ( STCALIB / 4 ) - 1 ;   //N=1 para 10ms
		STCURR = 0;

		ENABLE = 1;
		TICKINT = 1;
		CLKSOURCE = 1;
		return;
}

//-----------------------------------------------------------------------------
// Inicialización general del Kit de acuerdo al uso que se le dará.
//-----------------------------------------------------------------------------
void InicializarKit ( void )
{
	InicPLL();
	Inicializar_Teclado();
	Inicializar_Relay();
	Inicializar_RGB();
	Inicializar_Display7s();

// ESCRIBIR CODIGO DE OTRAS INICIALIZACIONES A PARTIR DE AQUI   <<<-----------------------
	InicSysTick();
}

