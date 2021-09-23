#ifndef SCREEN_H
#define SCREEN_H


#include "main.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

void draw_graphics(uint32_t *buffer);
void buffer_graphics(Chip8 *chip8, uint32_t *buffer);

#endif // SCREEN_H
