/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include "Aplicacion.h"

//variables globales
volatile uint8_t buffKey;				//Buffer de teclado
volatile uint8_t msgDisplay[DIGITOS];	//Buffer de display


int main(void) {
	uint8_t tecla;
	InicializarKit();
	
	 while(1)
	 {
		 tecla = Teclado();
		 switch(tecla)
		 {
	    	case T0:
	    		RGB_RED_ON;		//macro para encender el ROJO en el RGB
	            Display(T0,1);
	    		break;

	    	case T1:
	    		 RGB_RED_OFF;	//macro para apagar el ROJO en el RGB
	    		 RGB_BLUE_ON;	//ON azul
	   			 Display(T1,0);
	   			 break;

			case T2:
				RGB_BLUE_OFF;	//OFF azul
				RGB_GREEN_ON;	//ON verde
				Display(T2,1);
				break;

			case T3:
				RGB_GREEN_OFF;	//OFF verde
				RGB_BLUE_OFF;	//OFF azul
				RGB_RED_OFF;	//OFF rojo
				Display(T3,0);
				break;

			case T4:
				RGB_GREEN_ON;	//ON verde
				RGB_BLUE_ON;	//ON azul
				RGB_RED_ON;		//ON rojo
				Display(T4,1);
				break;

			default: break;
		 }
	 }
	 return 0 ;
}
