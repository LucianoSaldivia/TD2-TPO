#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#pragma comment(lib, "chip8_t.h")
#include <chip8_t.h>

//Las instrucciones se encuentran listadas en el orden de los opcodes
//https://en.wikipedia.org/wiki/CHIP-8

void cls(Chip8 *chip8);                     // 00E0 DISPLAY (clear screen)
void return_from_subrutine(Chip8 *chip8);   // 00EE FLOW
void jump(Chip8 *chip8);                    // 1NNN FLOW
void call_subroutine(Chip8 *chip8);         // 2NNN FLOW
void se_Vx_nn(Chip8 *chip8);                // 3XNN COND (skip equal)
void sne_Vx_nn(Chip8 *chip8);               // 4XNN COND (skip not equal)
void se_Vx_Vy(Chip8 *chip8);                // 5XY0 COND (skip equal)
void ld_Vx(Chip8 *chip8);                   // 6XNN CONST (load)
void add_Vx_imm(Chip8 *chip8);              // 7XNN CONST 
void move_Vx_Vy(Chip8 *chip8);              // 8XY0 ASSIGN
void or_Vx_Vy(Chip8 *chip8);                // 8XY1 BITOP
void and_Vx_Vy(Chip8 *chip8);               // 8XY2 BITOP
void xor_Vx_Vy(Chip8 *chip8);               // 8XY3 BITOP
void add_Vx_Vy(Chip8 *chip8);               // 8XY4 MATH
void sub_Vx_Vy(Chip8 *chip8);               // 8XY5 MATH
void shr(Chip8 *chip8);                     // 8XY6 BITOP (shift right)
void subn_Vx_Vy(Chip8 *chip8);              // 8XY7 MATH (subtract not equal)
void shl(Chip8 *chip8);                     // 8XYE BITOP (shift left)
void sne_Vx_vy(Chip8 *chip8);               // 9XY0 COND (skip not equal)
void ldi(Chip8 *chip8);                     // ANNN MEM (load I)
void jump_V0(Chip8 *chip8);                 // BNNN FLOW
void rnd(Chip8 *chip8);                     // CXNN RAND
void drw(Chip8 *chip8);                     // DXYN DISPLAY
void skp(Chip8 *chip8);                     // EX9E KEYOP (skip)
void skpn(Chip8 *chip8);                    // EXA1 KEYOP (skip not)
void ld_Vx_dt(Chip8 *chip8);                // FX07 TIMER (load)
void ld_Vx_k(Chip8 *chip8);                 // FX0A KEYOP (load)
void ld_dt_Vx(Chip8 *chip8);                // FX15 TIMER (load)
void ld_st_Vx(Chip8 *chip8);                // FX18 SOUND (load)
void add_i_Vx(Chip8 *chip8);                // FX1E MEM
void ld_F_Vx(Chip8 *chip8);                 // FX29 MEM
void st_bcd_Vx(Chip8 *chip8);               // FX33 BCD (set)
void st_V_regs(Chip8 *chip8);               // FX55 MEM (set)
void ld_V_regs(Chip8 *chip8);               // FX65 MEM (load)

#endif