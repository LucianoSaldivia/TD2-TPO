#include "screen.h"

void buffer_graphics(Chip8 *chip8, uint32_t *buffer) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
           if (chip8->screen[y][x] == 1)
        	   SetPixel(x,y);
        }
    }
}



