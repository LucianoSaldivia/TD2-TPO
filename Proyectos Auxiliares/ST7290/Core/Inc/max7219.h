/*
 * max7219.h
 *
 *  Created on: Jul 1, 2020
 *      Author: esala
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_
void llenar_max7219(uint8_t dato);
void dibujar_max7219(uint8_t *datos);
void inicializar_max7219(SPI_HandleTypeDef *spi, GPIO_TypeDef *GPIO_cs,
		uint16_t GPIO_Pin_cs);


#endif /* INC_MAX7219_H_ */
