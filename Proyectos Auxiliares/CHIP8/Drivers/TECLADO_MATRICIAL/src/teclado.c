/*
 * teclado.c
 *
 *  Created on: Sep 19, 2021
 *      Author: Luciano
 */

#include "main.h"

// Buffer de teclado
extern volatile uint8_t buffKey;

uint8_t Teclado( void )
{
	uint8_t tecla = NO_KEY;

	//if (buffKey != NO_KEY )
	//{
		tecla = buffKey;
		//buffKey = NO_KEY;
	//}
	return tecla;
}
void DriverTeclado(void)
{
	uint8_t CodigoActual ;
	CodigoActual = TecladoHW( );
	TecladoSW( CodigoActual );
}


void TecladoSW (uint8_t codAct){
   static uint8_t codAnt = NO_KEY;
   static uint8_t estado = REPOSO;
   uint8_t cont = 0; //no es necesario inicializarla

   if (codAct == NO_KEY)
   { //mientras NO se oprima tecla SIEMPRE
      codAnt = NO_KEY;	//entraré acá
      estado = REPOSO;
      buffKey = NO_KEY;
      return;
   }

   if (estado == DETECCION)
   {
      if (codAnt != codAct)
    	  codAnt = codAct;
      else {
    	  estado = CHEQUEO;
    	  cont = CANT_REBOTES;
      }
      return;
   }

   if (estado == CHEQUEO)
   {
      if (codAnt != codAct)
    	  estado = DETECCION;
      else if (cont)
    	  cont--;
      else {
    	  buffKey = codAct;
    	  estado = REPOSO;
    	  codAnt = NO_KEY;
      }
      return;
   }

   if (estado > EMERGENCIA) //por si perdí el control de la var de estado.
      estado = REPOSO;

   else{	//detecté una tecla por primera vez
      estado = DETECCION;
      codAnt = codAct;
   }
}


uint8_t TecladoHW (void)
{
	uint8_t Codigo = NO_KEY;
	COL_1_ON
	COL_2_OFF
	COL_3_OFF
	COL_4_OFF
	if (FILA_1) return 1;
	if (FILA_2) return 4;
	if (FILA_3) return 7;
	if (FILA_4) return 14;
	COL_1_OFF
	COL_2_ON
	COL_3_OFF
	COL_4_OFF
	if (FILA_1) return 2;
	if (FILA_2) return 5;
	if (FILA_3) return 8;
	if (FILA_4) return 0;
	COL_1_OFF
	COL_2_OFF
	COL_3_ON
	COL_4_OFF
	if (FILA_1) return 3;
	if (FILA_2) return 6;
	if (FILA_3) return 9;
	if (FILA_4) return 15;
	COL_1_OFF
	COL_2_OFF
	COL_3_OFF
	COL_4_ON
	if (FILA_1) return 10;
	if (FILA_2) return 11;
	if (FILA_3) return 12;
	if (FILA_4) return 13;
    return Codigo;
}


/***/
