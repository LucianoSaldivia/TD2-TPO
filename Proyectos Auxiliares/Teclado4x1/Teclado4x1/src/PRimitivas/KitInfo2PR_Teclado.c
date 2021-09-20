/**
 	\file KitInfo2PR_Teclado.c
 	\brief Primitiva de teclado
 	\details Valida para BASE y Expansion 3 y Expansion 4
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/
#include "Aplicacion.h"

// Buffer de teclado
extern uint8_t buffKey;

uint8_t Teclado( void )
{
	uint8_t tecla = NO_KEY;

	if (buffKey != NO_KEY )
	{
		tecla = buffKey;
		buffKey = NO_KEY;
	}
	return tecla;
}
