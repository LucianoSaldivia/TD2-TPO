 /**
 * Regs.h
 *
 *  Created on: 17/04/2012 -   Author: Mica y Chor
 *  modificado el 12/03/13 -   Author: Marcelo T. y G.
 *  modificado el 25/06/13 -   Author: GOS
 */

#ifndef REGSLPC1769_H_
#define REGSLPC1769_H_


	#define		__R		volatile const
	#define		__W		volatile
	#define		__RW		volatile

	typedef 	unsigned int 	uint32_t;
	typedef 	unsigned short 	uint16_t;
	typedef 	unsigned char 	uint8_t;

	//!< ////////////////Registros PINSEL//////////////////////////////
	//!< 0x4002C000UL : Direccion de inicio de los registros PINSEL
	#define		PINSEL		( ( __RW uint32_t  * ) 0x4002C000UL )

	#define		PINSEL0		PINSEL[0]	//!< PINSEL0--->P0[15:0] (0x4002C000)
	#define		PINSEL1		PINSEL[1]	//!< PINSEL1--->P0[31:16](0x4002C004)
	#define		PINSEL2		PINSEL[2]	//!< PINSEL2--->P1[15:0] (0x4002C008)
	#define		PINSEL3		PINSEL[3]	//!< PINSEL3--->P1[31:16](0x4002C00C)
	#define		PINSEL4		PINSEL[4]	//!< PINSEL4--->P2[15:0] (0x4002C010)
	#define		PINSEL5		PINSEL[5]	//!< PINSEL5--->P2[31:16] NOT USED
	#define		PINSEL6		PINSEL[6]	//!< PINSEL6--->P3[15:0] NOT USED
	#define		PINSEL7		PINSEL[7]	//!< PINSEL7--->P3[31:16] 0x4002C01C)
	#define		PINSEL8		PINSEL[8]	//!< PINSEL8--->P4[15:0]  NOT USED
	#define		PINSEL9		PINSEL[9]	//!< PINSEL9--->P4[31:16](0x4002C024)

	//!< ----------- Estados de PINSEL:
	#define		PINSEL_GPIO			0
	#define		PINSEL_FUNC1		1
	#define		PINSEL_FUNC2		2
	#define		PINSEL_FUNC3		3

	//!< //////////////////Registros PINMODE ///////////////////////////
	//!< 0x4002C040UL : Direccion de inicio de los registros de modo de los pines del GPIO
	#define	PINMODE		( ( __RW uint32_t  * ) 0x4002C040UL )

	#define		PINMODE0	PINMODE[0]		//!< 0x4002C040
	#define		PINMODE1	PINMODE[1]		//!< 0x4002C044
	#define		PINMODE2	PINMODE[2]		//!< 0x4002C048
	#define		PINMODE3	PINMODE[3]		//!< 0x4002C04C
	#define		PINMODE4	PINMODE[4]		//!< 0x4002C050
	#define		PINMODE5	PINMODE[5]		//!< 0x4002C054
	#define		PINMODE6	PINMODE[6]		//!< 0x4002C058
	#define		PINMODE7	PINMODE[7]		//!< 0x4002C05C
	#define		PINMODE9	PINMODE[9]		//!< 0x4002C064

	//!< ----------- Estados de PINMODE
	//!< 00	Pull Up resistor enable (reset value)		01	repeated mode enable
	//!< 11	Pull Down resistor enable					10	ni Pull Up ni Pull DOwn
	#define		PINMODE_PULLUP 		0
	#define		PINMODE_REPEAT 		1
	#define		PINMODE_NONE 		2
	#define		PINMODE_PULLDOWN 	3

	//!< ///////////////// REGISTROS PINMODE_OD ///////////////////////////
	//!< 0x4002C068UL : Direccion de inicio de los registros de control del modo OPEN DRAIN
	#define		PINMODE_OD		( ( __RW uint32_t  * ) 0x4002C068UL )

	#define		PINMODE_OD0		PINMODE_OD[0]
	#define		PINMODE_OD1		PINMODE_OD[1]
	#define		PINMODE_OD2		PINMODE_OD[2]
	#define		PINMODE_OD3		PINMODE_OD[3]
	#define		PINMODE_OD4		PINMODE_OD[4]

	//!< ////////////////// REGISTROS GPIOs //////////////////////////////
	//!< 0x2009C000UL : Direccion de inicio de los registros de GPIOs
	#define	GPIOs		( ( __RW uint32_t  * ) 0x2009C000UL )

	/*	*						*
		*************************
		*		FIODIR			*	0x2009C000
		*************************
		*		RESERVED		*	0x2009C004
		*************************
		*		RESERVED		*	0x2009C008
		*************************
		*		RESERVED		*	0x2009C00C
		*************************
		*		FIOMASK			*	0x2009C010
		*************************
		*		FIOPIN			*	0x2009C014
		*************************
		*		FIOSET			*	0x2009C018
		*************************
		*		FIOCLR			*	0x2009C01C
		*************************
		*						*
		*						*
	*/
	#define		FIO0DIR		GPIOs[0]	//!< 0x2009C000
	#define		FIO1DIR		GPIOs[8]	//!< 0x2009C020
	#define		FIO2DIR		GPIOs[16]	//!< 0x2009C040
	#define		FIO3DIR		GPIOs[24]	//!< 0x2009C060
	#define		FIO4DIR		GPIOs[32]	//!< 0x2009C080

	#define		FIO0MASK	GPIOs[4]	//!< 0x2009C010
	#define		FIO1MASK	GPIOs[12]	//!< 0x2009C030
	#define		FIO2MASK	GPIOs[20]	//!< 0x2009C050
	#define		FIO3MASK	GPIOs[28]	//!< 0x2009C070
	#define		FIO4MASK	GPIOs[36]	//!< 0x2009C090

	#define		FIO0PIN		GPIOs[5]	//!< 0x2009C014
	#define		FIO1PIN		GPIOs[13]	//!< 0x2009C034
	#define		FIO2PIN		GPIOs[21]	//!< 0x2009C054
	#define		FIO3PIN		GPIOs[29]	//!< 0x2009C074
	#define		FIO4PIN		GPIOs[37]	//!< 0x2009C094

	#define		FIO0SET		GPIOs[6]	//!< 0x2009C018
	#define		FIO1SET		GPIOs[14]	//!< 0x2009C038
	#define		FIO2SET		GPIOs[22]	//!< 0x2009C058
	#define		FIO3SET		GPIOs[30]	//!< 0x2009C078
	#define		FIO4SET		GPIOs[38]	//!< 0x2009C098

	#define		FIO0CLR		GPIOs[7]	//!< 0x2009C01C
	#define		FIO1CLR		GPIOs[15]	//!< 0x2009C03C
	#define		FIO2CLR		GPIOs[23]	//!< 0x2009C05C
	#define		FIO3CLR		GPIOs[31]	//!< 0x2009C07C
	#define		FIO4CLR		GPIOs[39]	//!< 0x2009C09C

	// dirección en FIODIR
	#define 	ENTRADA			0
	#define 	SALIDA			1


//-----------------------------------------------------------------------------
// NVIC
//-----------------------------------------------------------------------------

	#define		ISER 		( ( __RW uint32_t  * ) 0xE000E100UL )
	#define 	ISER0		ISER[0]
	#define 	ISER1		ISER[1]

	#define		ICER 		( ( __RW uint32_t  * ) 0xE000E180UL )
	#define		ICER0		ICER[0]
	#define		ICER1		ICER[1]

	#define		ISPR 		( ( __RW uint32_t  * ) 0xE000E200UL )
	#define		ISPR0		ISPR[0]
	#define		ISPR1		ISPR[1]

	#define		ICPR 		( ( __RW uint32_t  * ) 0xE000E280UL )
	#define		ICPR0		ICPR[0]
	#define		ICPR1		ICPR[1]

	#define		IABR 		( ( __RW uint32_t  * ) 0xE000E300UL )
	#define		IABR0		IABR[0]
	#define		IABR1		IABR[1]

	#define		IPR 		( ( __RW uint32_t  * ) 0xE000E400UL )
	#define		IPR0		IPR[0]
	#define		IPR1		IPR[1]
	#define		IPR2		IPR[2]
	#define		IPR3		IPR[3]
	#define		IPR4		IPR[4]
	#define		IPR5		IPR[5]
	#define		IPR6		IPR[6]
	#define		IPR7		IPR[7]
	#define		IPR8		IPR[8]

	#define		STIR_ 		( ( __RW uint32_t  * ) 0xE000EF00UL )
	#define		STIR 		STIR_[0]


//-----------------------------------------------------------------------------
// Interrupciones Externas
//-----------------------------------------------------------------------------
	#define		EXTINT_ 	( ( __RW uint32_t  * ) 0x400FC140UL )
	#define		EXTINT		EXTINT_[0]

	#define		EXTMODE_ 	( ( __RW uint32_t  * ) 0x400FC148UL )
	#define		EXTMODE		EXTMODE_[0]

	#define		EXTPOLAR_ 	( ( __RW uint32_t  * ) 0x400FC14CUL )
	#define 	EXTPOLAR	EXTPOLAR_[0]

	#define 	EINT0  	0
	#define 	EINT1  	1
	#define 	EINT2  	2
	#define 	EINT3  	3


//-----------------------------------------------------------------------------
// Interrupciones Externas GPIO
//-----------------------------------------------------------------------------
	#define		IOIntStatus_ 		( ( __RW uint32_t  * ) 0x40028080UL )
	#define		IOIntStatus		IOIntStatus_[0]

	// P0
	#define		IO0IntStatR_ 		( ( __RW uint32_t  * ) 0x40028084UL )
	#define		IO0IntStatR		IO0IntStatR_[0]

	#define		IO0IntStatF_ 		( ( __RW uint32_t  * ) 0x40028088UL )
	#define		IO0IntStatF		IO0IntStatF_[0]

	#define		IO0IntClr_ 		( ( __RW uint32_t  * ) 0x4002808CUL )
	#define		IO0IntClr		IO0IntClr_[0]

	#define		IO0IntEnR_ 		( ( __RW uint32_t  * ) 0x40028090UL )
	#define		IO0IntEnR		IO0IntEnR_[0]

	#define		IO0IntEnF_ 		( ( __RW uint32_t  * ) 0x40028094UL )
	#define		IO0IntEnF		IO0IntEnF_[0]

	// P2
	#define		IO2IntStatR_ 		( ( __RW uint32_t  * ) 0x400280A4UL )
	#define		IO2IntStatR			IO2IntStatR_[0]

	#define		IO2IntStatF_ 		( ( __RW uint32_t  * ) 0x400280A8UL )
	#define		IO2IntStatF			IO2IntStatF_[0]

	#define		IO2IntClr_ 		( ( __RW uint32_t  * ) 0x400280ACUL )
	#define		IO2IntClr		IO2IntClr_[0]

	#define		IO2IntEnR_ 		( ( __RW uint32_t  * ) 0x400280B0UL )
	#define		IO2IntEnR		IO2IntEnR_[0]

	#define		IO2IntEnF_ 		( ( __RW uint32_t  * ) 0x400280B4UL )
	#define		IO2IntEnF		IO2IntEnF_[0]


	//!< ///////////////////   PCONP   //////////////////////////
	//!<  Power Control for Peripherals register (PCONP - 0x400F C0C4) [pag. 62 user manual LPC1769]
	//!< 0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
	#define 	PCONP	(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))


	//!< ///////////////////   PCLKSEL   //////////////////////////
	//!< Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
	//!< 0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los CLKs de los dispositivos:
	#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
	//!< Registros PCLKSEL
	#define		PCLKSEL0	PCLKSEL[0]
	#define		PCLKSEL1	PCLKSEL[1]


	//!< /////////////		SYSTICK		///////////////////////////
	//!< Tipo de dato específico para manejar el SYSTICK
	typedef struct
	{
		union{
			__RW uint32_t _STCTRL;
			struct{
				__RW uint32_t _ENABLE:1;
				__RW uint32_t _TICKINT:1;
				__RW uint32_t _CLKSOURCE:1;
				__RW uint32_t _RESERVED0:12;
				__RW uint32_t _COUNTFLAG:1;
				__RW uint32_t _RESERVED1:16;
			}bits;
		};
		__RW uint32_t _STRELOAD;
		__RW uint32_t _STCURR;
		__R uint32_t  _STCALIB;
	}systick_t;

	//!< 0xE000E010UL: Registro de control del SysTick:
	#define 	DIR_SYSTICK		( (systick_t *) 0xE000E010UL )

	#define		STCTRL		DIR_SYSTICK->_STCTRL
		#define	ENABLE			DIR_SYSTICK->bits._ENABLE
		#define	TICKINT			DIR_SYSTICK->bits._TICKINT
		#define	CLKSOURCE		DIR_SYSTICK->bits._CLKSOURCE
		#define	COUNTFLAG		DIR_SYSTICK->bits._COUNTFLAG
	#define		STRELOAD	DIR_SYSTICK->_STRELOAD
	#define		STCURR		DIR_SYSTICK->_STCURR
	#define		STCALIB		DIR_SYSTICK->_STCALIB

	#define 	N 		1	//Si N=1, Systick interrumpe cada 10ms.

#endif /* REGS_H_ */
