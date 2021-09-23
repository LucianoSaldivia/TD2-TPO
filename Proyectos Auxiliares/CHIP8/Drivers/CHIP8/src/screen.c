#include "screen.h"

void graficar(Chip8 *chip8){
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
           if (chip8->screen[y][x] == 1)
        	   SetPixel(x,y);
        }
    }
    ST7920_Update();
}



