#ifndef CHIP8_H
#define CHIP8_H

#include "instructions.h"


//Mapeo del teclado
const static uint8_t KEYMAP[NUM_KEYS] = {
    0, // 0
    1, // 1
    2, // 2
    3, // 3
    4, // 4
    5, // 5
    6, // 6
    7, // 7
    8, // 8
    9, // 9
    10, // A
    11, // B
    12, // C
    13, // D
    14, // E
    15  // F
};

uint8_t rom_buffer [4096];//buffer donde se va copiar la ROM de la SD

void load_rom(Chip8 *chip8);
void init_system(Chip8 *chip8);
void fallo (uint8_t codigo_falla);
uint8_t mi_rand(void);

uint16_t fetch_opcode(Chip8 *chip8);
void exec_instruction(Chip8 *chip8);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);


#endif // CHIP8_H
