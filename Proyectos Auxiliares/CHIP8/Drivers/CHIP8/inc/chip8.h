#ifndef CHIP8_H
#define CHIP8_H

#include "instructions.h"


// Keymap for the emulator. Comments are the orignal
// key on the hex keypad
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

uint8_t rom_buffer [4096/2];

void load_rom(Chip8 *chip8, const char *rom_filename);
void init_system(Chip8 *chip8);
void reset_system(Chip8 *chip8);
uint16_t fetch_opcode(Chip8 *chip8);
void execute_instruction(Chip8 *chip8, int logging);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);

// Debugging functions
void print_regs(Chip8 *chip8);
void print_stack(Chip8 *chip8);
void print_keyboard(Chip8 *chip8);


#endif // CHIP8_H
