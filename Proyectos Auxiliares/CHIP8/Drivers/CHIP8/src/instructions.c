#include "instructions.h"
#include "screen.h"

//Opcode 00E0: Limpio pantalla
void cls(Chip8 *chip8) {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            chip8->screen[i][j] = 0;
        }
    }

    chip8->pc_reg += 2;
}


/*
* Opcode 00EE: Vuelvo de una subrutina
* hago unstacking, sp_reg decrementado
*/
void volver_subroutina(Chip8 *chip8) {
    chip8->sp_reg--;
    chip8->pc_reg = chip8->stack[chip8->sp_reg];
    chip8->pc_reg += 2;
}


//Opcode 1NNN: salto a la dir NNN

void jump(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->pc_reg = nnn;
}


/*
* Opcode 2NNN: Call Subroutina en  NNN
* sp_reg incrementedo, pc_reg pushedeado al stack, pc_reg seteado a NNN
*/
void call_subroutina(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->stack[chip8->sp_reg] = chip8->pc_reg;
    chip8->sp_reg++;
    chip8->pc_reg = nnn;
}


/*
* Opcode 3XKK: Salto a proxima instruccion
* Incremento el pc_reg en 4 (2 instructiones) si  V[x] == KK
*/
void se_Vx_kk(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;

    if (chip8->V[target_v_reg] == kk) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode 4XKK: Salto a la proxima instruccion
* Incremento el pc_reg en 4 (2 instructionss) si   V[x] != KK
*/
void sne_Vx_kk(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;

    if (chip8->V[target_v_reg] != kk) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode 5XY0: Salto a la proxima instruccion
* Incremento el pc_reg en 4 (2 instructioness) si  V[x] == V[Y]
*/
void se_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    if (chip8->V[target_v_reg_x] == chip8->V[target_v_reg_y]) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode 6XKK: Cargo el inmediato Vx
* Seteo el valor kk    en el registro V [X]
*/
void ld_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;

    chip8->V[target_v_reg] = kk;
    chip8->pc_reg += 2;
}


/*
* Opcode 7XKK: Hace VX = VX + KK
*/
void add_Vx_imm(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    
    // TODO: What if there is overflow?
    chip8->V[target_v_reg] += kk;;
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY0: Load Vx, Vy
	Hace VX = VY. Almacena el valor del registro VY en el registro VX
*/
void move_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    
    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}


/*
 * 	Opcode 8XY1: OR Vx, Vy
*/
void or_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    chip8->V[target_v_reg_x] = (chip8->V[target_v_reg_x] | chip8->V[target_v_reg_y]);
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY2: AND Vx, Vy
*/
void and_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    chip8->V[target_v_reg_x] = (chip8->V[target_v_reg_x] & chip8->V[target_v_reg_y]);
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY3: XOR Vx, Vy
*/
void xor_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    chip8->V[target_v_reg_x] = (chip8->V[target_v_reg_x] ^ chip8->V[target_v_reg_y]);
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY4: ADD Vx, Vy
* V[X]= V[X] + V[Y] stored in
* if sum > 255, V[F] register (carry) i = 1, else 0
* V[X] =  LSB (sum)
*/
void add_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint16_t sum = (chip8->V[target_v_reg_x] + chip8->V[target_v_reg_y]);

    if (sum > 255) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }

    chip8->V[target_v_reg_x] = (sum & 0xFF);
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY5: SUB Vx, Vy
* V[X]= V[X] - V[Y] stored in
* If V[X] > V[Y], V[F] registro (borrow) en 1,  sino 0
*/
void sub_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    if (chip8->V[target_v_reg_x] > chip8->V[target_v_reg_y]) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }

    chip8->V[target_v_reg_x] -= chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY6: SHR Vx
* V[X] = V[X] >> 1
* if  LSb  V[X] == 1, V[F] = 1, else 0
*/
void shr(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;


    if (chip8->V[target_v_reg_x] % 2 == 1) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_x] >> 1;
    chip8->pc_reg += 2;
}

//PABLO_PUTO.COM
/*
* Opcode 8XY7: SUBN Vx, Vy
* V[X]=V[Y] - V[X]
* If V[Y] > V[X], V[F] registro (borrow) = 1, else 0
*/
void subn_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    if (chip8->V[target_v_reg_y] > chip8->V[target_v_reg_x]) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_y] - chip8->V[target_v_reg_x];
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY6: SHL Vx
* V[X] = V[X] << 1
* If MSb of V[X] == 1, V[F] = 1, else 0
*/
void shl(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;

    // check if the MSb is 1
    if ((chip8->V[target_v_reg_x] & 10000000) == 1) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_x] << 1;
    chip8->pc_reg += 2;
}


/*
* Opcode 9XY0: Salta instruccion
* Incremento el pc_reg en 4 (2 instructiones) if  V[X] != V[Y]
*/
void sne_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_y_reg = (chip8->current_op & 0x00F0) >> 4;

    if (chip8->V[target_v_reg] != chip8->V[target_y_reg]) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode ANNN:
* Cargo el  Index register con un valor
*/
void ldi(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->I_reg = nnn;
    chip8->pc_reg += 2;
}


/*
* Opcode BNNN: Jump + V[0]
*/
void jump_V0(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->pc_reg = (nnn + chip8->V[0]);
}


/*
* Opcode CXKK: Random
* Random Num between 0 - 255
* Store the result in V[X]
*/
//TODO:AAAA
void rnd(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    uint8_t random_num = mi_rand() % 256;

    chip8->V[target_v_reg] = random_num & kk;
    chip8->pc_reg += 2;
}


/*
* Opcode DXYN: Display N-byte sprite at ram[I_reg]
* Dibujo sprite en la posicion V[X], V[Y].
*/
void drw(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint8_t sprite_height = chip8->current_op & 0x000F;
    uint8_t x_location = chip8->V[target_v_reg_x];
    uint8_t y_location = chip8->V[target_v_reg_y];
    uint8_t pixel;


    chip8->V[0xF] = FALSE;
    for (int y_coordinate = 0; y_coordinate < sprite_height; y_coordinate++) {
        pixel = chip8->ram[chip8->I_reg + y_coordinate];
        for (int x_coordinate = 0; x_coordinate < 8; x_coordinate++) {
            if ((pixel & (0x80 >> x_coordinate)) != 0) {
                if (chip8->screen[y_location + y_coordinate][x_location + x_coordinate] == 1) {
                    chip8->V[0xF] = TRUE;
                }
                if ( chip8->screen[y_location + y_coordinate][x_location + x_coordinate] ^= 1){
                	SetPixel(2*(x_location + x_coordinate),2*(y_location + y_coordinate));
                }
                else{
                	ClearPixel(2*(x_location + x_coordinate),2*(y_location + y_coordinate));
                }
            }
        }
    }
    ST7920_Update();
    chip8->pc_reg += 2;
}


/*
* Opcode EX9E:Salta la proxima instruccion si una tecla fue presionada con el valor V[X]
*/
void skp(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t vX_value = chip8->V[target_v_reg];

    if (chip8->keyboard[vX_value] != FALSE) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode EXA1: Salta la proxima instruccion si una tecla  NO fue presionada con el valor V[X]
*/
void sknp(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t vX_value = chip8->V[target_v_reg];

    if (chip8->keyboard[vX_value] == FALSE) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode FX07: Load Vx, DT
* V[X] = delay_timer
*/
void ld_Vx_dt(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->V[target_v_reg] = chip8->delay_timer;
    chip8->pc_reg += 2;
}


/*
* Opcode FX0A: Load Vx, K
* Espero a que apreten una tecla
* V[X] set to value of key (K) pressed
*/
void ld_Vx_k(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->was_key_pressed = FALSE;

    for (int i = 0; i < NUM_KEYS; i++) {
        if (chip8->keyboard[i] != FALSE) {
            chip8->V[target_v_reg] = i;
            chip8->was_key_pressed = TRUE;
        }
    }

    if (!chip8->was_key_pressed) {
        return;
    }

    chip8->pc_reg += 2;
}


/*
* Opcode FX15: Load DT, Vx
* delay_timer =  V[X]
*/
void ld_dt_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->delay_timer = chip8->V[target_v_reg];
    chip8->pc_reg += 2;
}


/*
* Opcode FX18: Load ST, Vx
* sound_timer = V[X]
*/
void ld_st_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->sound_timer = chip8->V[target_v_reg];
    chip8->pc_reg += 2;
}


/*
* Opcode FX1E:
* I_reg=I_reg + V[X]
*/
void add_i_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->I_reg = chip8->I_reg + chip8->V[target_v_reg];
    chip8->pc_reg += 2;
}


/*
* Opcode FX29: LD F, VX
* I_reg = V[X] * 5
*/
void ld_F_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->I_reg = (chip8->V[target_v_reg] * 0x5);
    chip8->pc_reg += 2;
}


/*
* Opcode FX33:
* Reprensento en BCD a V[X]
*  I (centenas) I+1 (decenas) y I+2 (unidades)
	VER REFERENCIA
* http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
*/
void st_bcd_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->ram[chip8->I_reg] = chip8->V[target_v_reg] / 100;                 // MSb
    chip8->ram[chip8->I_reg + 1] = (chip8->V[target_v_reg] / 10) % 10;
    chip8->ram[chip8->I_reg + 2] = (chip8->V[target_v_reg] % 100) % 10;      // LSb
    chip8->pc_reg += 2;
}


/*
* Opcode FX55:
* I_reg = V[0] - V[X]
*/
void st_V_regs(Chip8 *chip8) {
    uint8_t end_ld_v_reg = (chip8->current_op & 0x0F00) >> 8;

    for (int i = 0; i <= end_ld_v_reg; i++) {
        chip8->ram[chip8->I_reg + i] = chip8->V[i];
    }

    // TODO: Does I_reg need to change?
    chip8->I_reg += (end_ld_v_reg + 1);

    chip8->pc_reg += 2;
}


/*
* Opcode FX65:
* Guardo los valores de la memoria RAM en el registro V
*/
void ld_V_regs(Chip8 *chip8) {
    uint8_t end_ld_v_reg = (chip8->current_op & 0x0F00) >> 8;

    for (int i = 0; i <= end_ld_v_reg; i++) {
        chip8->V[i] = chip8->ram[chip8->I_reg + i];
    }

    chip8->I_reg += (end_ld_v_reg + 1);

    chip8->pc_reg += 2;
}
