#include "screen.h"

void graficar(Chip8 *chip8){
	int y;
	for(y=0;y<DISPLAY_LENGTH_IMG;image[y++]=0);
	for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
           if (chip8->screen[y][x] == 1){
        	   SetPixel(x,y);

           }
        }
    }
  ST7920_Update();
}



