/**
 	\file KitInfo2FW_7Seg.c
 	\brief Drivers del display de 7 segmentos
 	\details Expansion 2
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "Aplicacion.h"

extern volatile uint8_t msgDisplay[];		//!< Buffer de display
void BarridoDisplay( void );
/**
	\fn void BarridoDisplay( void )
	\brief Barrido del display de 7 segmentos
 	\param void
	\return void
*/

void BarridoDisplay( void )
{
	uint8_t auxiliar;
	static uint8_t	digito = 0;

	SetPIN(digito0,OFF);
	SetPIN(digito1,OFF);
	SetPIN(digito2,OFF);
	SetPIN(digito3,OFF);
	SetPIN(digito4,OFF);
	SetPIN(digito5,OFF);

	auxiliar = msgDisplay[digito];

	SetPIN(segmento_a, (auxiliar & (uint8_t)0x01));
	SetPIN(segmento_b, (( auxiliar >> 1 ) & (uint8_t)0x01));
	SetPIN(segmento_c, (( auxiliar >> 2 ) & (uint8_t)0x01));
	SetPIN(segmento_d, (( auxiliar >> 3 ) & (uint8_t)0x01));
	SetPIN(segmento_e, (( auxiliar >> 4 ) & (uint8_t)0x01));
	SetPIN(segmento_f, (( auxiliar >> 5 ) & (uint8_t)0x01));
	SetPIN(segmento_g, (( auxiliar >> 6 ) & (uint8_t)0x01));
	SetPIN(segmento_dp,(( auxiliar >> 7 ) & (uint8_t)0x01));


	switch( digito )
	{
		case DIGITO_5:
			SetPIN(digito5,ON); break;
		case DIGITO_4:
			SetPIN(digito4,ON); break;
		case DIGITO_3:
			SetPIN(digito3,ON); break;
		case DIGITO_2:
			SetPIN(digito2,ON); break;
		case DIGITO_1:
			SetPIN(digito1,ON); break;
		case DIGITO_0:
			SetPIN(digito0,ON); break;
	}

	// Incremento el indice del display
	digito++;
	digito %= DIGITOS;
}

