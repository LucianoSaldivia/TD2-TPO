#ifndef CHIP8_T_H
#define CHIP8_T_H

#include <stdint.h>

/*
Definiciones de la estructura del chip8 y 
algunas constantes utilizadas por el programa
*/

#define NUM_KEYS 16
#define NUM_V_REGISTERS 16
#define TOTAL_RAM 4096
#define STACK_SIZE 16
#define FONTSET_SIZE 80
#define PC_START 0X200
#define TIMER_MAX 255

#define CHIP8_RAM_START_ADDR 0X000
#define CHIP8_RAM_END_ADDR 0X1FF
#define PROGRAM_START_ADDR 0X200
#define PROGRAM_END_ADDR 0XFFF

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#define TRUE 1
#define FALSE 0

typedef struct Chip8_t Chip8;

const static uint8_t FONTSET[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

struct Chip8_t {
    uint8_t ram[TOTAL_RAM];         //4k de memoria
    uint16_t stack[STACK_SIZE];     //16 niveles de stack

    //Registros
    uint8_t V[NUM_V_REGISTERS];     //registros de proposito general (0-14) y carry flag (15)
    uint8_t I_reg;                  //index register
    uint16_t pc_reg;                //program count register
    uint16_t sp_register;           //stack pointer register

    //Timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t current_op;            //opcode que se ejecuta actualmente

    //Pantalla
    uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

    //Input
    uint8_t keyboard[NUM_KEYS];
    uint8_t was_key_pressed;

    //Status flag del emulador
    uint8_t is_running_flag;
    uint8_t draw_screen_flag;
    uint8_t is_paused_flag;
};

#endif