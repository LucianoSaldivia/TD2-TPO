/*
 * teclado.h
 *
 *  Created on: Sep 19, 2021
 *      Author: Luciano
 */

#ifndef TECLADO_MATRICIAL_INC_TECLADO_H_
#define TECLADO_MATRICIAL_INC_TECLADO_H_

#define COL_1_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
#define COL_1_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
#define COL_2_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#define COL_2_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
#define COL_3_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
#define COL_3_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
#define COL_4_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
#define COL_4_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

#define FILA_1 HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_9)
#define FILA_2 HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_8)
#define FILA_3 HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_7)
#define FILA_4 HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_6)


#define 	CANT_REBOTES	10 //valor empírico
#define		REPOSO			0
#define		DETECCION		1
#define		CHEQUEO			2
#define		EMERGENCIA		CHEQUEO
#define		NO_KEY			(uint8_t) 0xFF

void DriverTeclado(void);
void TecladoSW (uint8_t codAct);
uint8_t TecladoHW (void);
uint8_t Teclado( void );


#endif /* TECLADO_MATRICIAL_INC_TECLADO_H_ */
