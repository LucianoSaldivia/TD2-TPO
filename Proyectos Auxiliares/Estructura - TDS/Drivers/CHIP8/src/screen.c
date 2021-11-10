#include "screen.h"
extern SPI_HandleTypeDef hspi2;

void init_graphics (void){
  delay_init();
  ST7920_Init(&hspi2, GPIOB, GPIO_PIN_12);
	ST7920_GraphicMode(0);
	ST7920_Clear();
}
void graficar(Chip8 *chip8){
/*
	FUNCION QUE QUEDO DE LA PRIMERA IMPLEMENTACION
	*/
}


