#include "screen.h"
void init_graphics (void){
  delay_init();
	ST7920_Init();
	ST7920_GraphicMode(1);
	ST7920_Clear();
}
void graficar(Chip8 *chip8){
	int y;
	for(y=0;y<DISPLAY_LENGTH_IMG;image[y++]=0);
	for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
          if (chip8->screen[y][x] == 1){
        	   SetPixel(2*x,2*y);
           }
        }
    }
  ST7920_Update();
}


