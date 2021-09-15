#include "instrucciones.h"

// Opcode 00E0: Clears the screen
void cls (Chip8 *chip8){
    int i, j = 0;

    for (i = 0 ; i < SCREEN_HEIGHT ; i++ ) {
        for (j = 0 ; j < SCREEN_WIDTH ; j++) {
            chip8->screen[i][j] = 0;
        }
    }

    chip8->draw_screen_flag = TRUE;
    chip8->pc_reg += 2;
}

// Opcode 00EE: Returns from a subroutine
void return_from_subrutine (Chip8 *chip8){
    chip8->sp_reg--;
    chip8->pc_reg = chip8->stack[chip8->sp_reg];
    chip8->sp_reg += 2;
}

// Opcode 1NNN: Jumps to adress NNN
void jump (Chip8 *chip8){
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->pc_reg = nnn;
}

// Opcode 2NNN: Calls subroutine at NNN
void call_subroutine (Chip8 *chip8){
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->stack[chip8->sp_reg] = chip8->pc_reg;
    chip8->sp_reg++;
    chip8->pc_reg = nnn;
}

// Opcode 3XNN: Skips the next instruction if VX equals NN
void se_Vx_nn (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0XF000) >> 8;
    uint8_t nn = chip8->current_op & 0X00FF;

    if (chip8->V[target_v_reg] == nn) {
        chip8->sp_reg += 4;
    }
    else {
        chip8->sp_reg += 2;
    }
}

// Opcode 4XNN: Skips the next instruction if VX does not equal NN
void sne_Vx_nn (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    uint8_t nn = chip8->current_op & 0X00FF;

    if (chip8->V[target_v_reg] != nn) {
        chip8->sp_reg += 4;
    }
    else {
        chip8->sp_reg += 2;
    }
}

// Opcode 5XY0: Skips the next instruction if VX equals VY
void se_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    if (chip8->V[target_v_reg_x] != chip8->V[target_v_reg_y]) {
        chip8->sp_reg += 4;
    }
    else {
        chip8->sp_reg += 2;
    }
}

// Opcode 6XNN: Sets VX to NN
void ld_Vx (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    uint8_t nn = chip8->current_op & 0X00FF;

    chip8->V[target_v_reg] = nn;
    chip8->pc_reg += 2;
}

// Opcode 7XNN: Adds NN to VX. (Carry flag is not changed)
void add_Vx_imm (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    uint8_t nn = chip8->current_op & 0X00FF;

    chip8->V[target_v_reg] += nn;
    chip8->pc_reg += 2;
}

// Opcode 8XY0: Sets VX to the value of VY
void move_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}

// Opcode 8XY1: Sets VX to VX or VY. (Bitwise OR operation)
void or_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_x] | chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}

// Opcode 8XY2: Sets VX to VX and VY. (Bitwise AND operation)
void and_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_x] & chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}

// Opcode 8XY3: Sets VX to VX xor VY
void xor_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_x] ^ chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}

// Opcode 8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not
void add_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;
    uint16_t sum = chip8->V[target_v_reg_x] + chip8->V[target_v_reg_y];

    if (sum > 255) {
        chip8->V[0x0F] = 1;
    }
    else {
        chip8->V[0x0F] = 0;
    }

    chip8->V[target_v_reg_x] = sum & 0XFF;
    chip8->pc_reg += 2;
}

// Opcode 8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not
void sub_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    if (chip8->V[target_v_reg_x] > chip8->V[target_v_reg_y]) {
        chip8->V[0x0F] = 1;
    }
    else {
        chip8->V[0x0F] = 0;
    }

    chip8->V[target_v_reg_x] -= chip8->V[target_v_reg_y];
    chip8->pc_reg += 2;
}

// Opcode 8XY6: Stores the least significant bit of VX in VF and then shifts VX to the right by 1
void shr (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->V[0X0F] = chip8->V[target_v_reg] & 0x0F;
    chip8->V[target_v_reg] = chip8->V[target_v_reg] >> 1;
    chip8->pc_reg += 2;
}

// Opcode 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not
void subn_Vx_Vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    if (chip8->V[target_v_reg_x] > chip8->V[target_v_reg_y]) {
        chip8->V[0x0F] = 1;
    }

    else {
        chip8->V[0x0F] = 0;
    }

    chip8->V[target_v_reg_x] = chip8->V[target_v_reg_y] - chip8->V[target_v_reg_x];
    chip8->pc_reg += 2;
}

// Opcode 8XYE: Stores the most significant bit of VX in VF and then shifts VX to the left by 1
void shl (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->V[0X0F] = chip8->V[target_v_reg] & 0xF0;
    chip8->V[target_v_reg] = chip8->V[target_v_reg] << 1;
    chip8->pc_reg += 2;
}

// Opcode 9XY0: Skips the next instruction if VX does not equal VY
void sne_Vx_vy (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;

    if (chip8->V[target_v_reg_x] != chip8->V[target_v_reg_y]) {
        chip8->pc_reg += 4;
    }

    else {
        chip8->pc_reg += 2;
    }
}

// Opcode ANNN: Sets I to the address NNN
void ldi (Chip8 *chip8){
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->I_reg = nnn;
    chip8->pc_reg += 2;
}

// Opcode BNNN: Jumps to the address NNN plus V0
void jump_V0 (Chip8 *chip8){
    uint16_t nnn = chip8->current_op & 0X0FFF;

    chip8->pc_reg = nnn + chip8->V[0];
}

// Opcode CXNN: Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
void rnd (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    uint8_t nn = chip8->current_op & 0X00FF;
    uint8_t rand_num = rand() % 256;

    chip8->V[target_v_reg] = rand_num & nn;
}

// Opcode DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N+1 pixels.
//      Each row of 8 pixels is read as bit-coded starting from memory location I; I value does not change after the
//      execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set
//      to unset when the sprite is drawn, and to 0 if that does not happen
void drw (Chip8 *chip8){
    uint8_t target_v_reg_x = (chip8->current_op & 0X0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0X00F0) >> 4;
    uint8_t sprite_height  =  chip8->current_op & 0X000F;

    uint8_t X_location = chip8->V[target_v_reg_x];
    uint8_t y_location = chip8->V[target_v_reg_y];
    uint8_t pixel;

    int y_coordinate, x_coordinate = 0;

    //Resetea el registro de colision
    chip8->V[0XF] = FALSE;
    for (y_coordinate = 0 ; y_coordinate <  sprite_height ; y_coordinate++) {
        pixel = chip8->ram[chip8->I_reg + y_coordinate];
        for (x_coordinate = 0 ; x_coordinate <  8 ; x_coordinate++) {
            //Verifica cada pixel de la fila
            if ((pixel & (0X80 >> x_coordinate)) != 0 ) {
                //Si el pixel se encuentra dibujado
                if (chip8->screen[y_location + y_coordinate][X_location + x_coordinate] == 1) {
                    //Setea el registro de colision
                    chip8->V[0X0F] = TRUE;
                }
                //Dibuja el pixel
                chip8->screen[y_location + y_coordinate][X_location + x_coordinate] ^= 1;
            }
        }
    }

    chip8->draw_screen_flag = TRUE;
    chip8->pc_reg += 2;
}

// Opcode EX9E: Skips the next instruction if the key stored in VX is pressed
void skp (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    uint8_t vx_value = chip8->V[target_v_reg];

    if (chip8->keyboard[vx_value] != FALSE) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}

// Opcode EXA1: Skips the next instruction if the key stored in VX is not pressed
void skpn (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    uint8_t vx_value = chip8->V[target_v_reg];

    if (chip8->keyboard[vx_value] == FALSE) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}

// Opcode FX07: Sets VX to the value of the delay timer
void ld_Vx_dt (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->V[target_v_reg] = chip8->delay_timer;
    chip8->pc_reg += 2;
}

// Opcode FX0A: A key press is awaited, and then stored in VX. (Blocking Operation. All instruction
//      halted until next key event)
void ld_Vx_k (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;
    int i = 0;

    chip8->was_key_pressed = FALSE;

    for (i = 0 ; i < NUM_KEYS ; i++) {
        if (chip8->keyboard[i] == FALSE) {
            chip8->V[target_v_reg] = i;
            chip8->was_key_pressed = TRUE;
        }
    }

    if (!chip8->was_key_pressed)
        return;

    chip8->pc_reg += 2;
}

// Opcode FX15: Sets the delay timer to VX
void ld_dt_Vx (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->delay_timer = chip8->V[target_v_reg];
    chip8->pc_reg += 2;
}

// Opcode FX18: Sets the sound timer to VX
void ld_st_Vx (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->sound_timer = chip8->V[target_v_reg];
    chip8->pc_reg += 2;
}

// Opcode FX1E: Adds VX to I. VF is not affected
void add_i_Vx (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->I_reg += chip8->V[target_v_reg];
    chip8->pc_reg += 2;
}

// Opcode FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal)
//      are represented by a 4x5 font
void ld_F_Vx (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->I_reg = (chip8->current_op & 0X0F00) >> 8;
    chip8->pc_reg += 2;
}

// Opcode FX33: Stores the binary-coded decimal representation of VX, with the most significant of three
//      digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2.
//      (In other words, take the decimal representation of VX, place the hundreds digit in memory at location
//      in I, the tens digit at location I+1, and the ones digit at location I+2.)
void st_bcd_Vx (Chip8 *chip8){
    uint8_t target_v_reg = (chip8->current_op & 0X0F00) >> 8;

    chip8->ram[chip8->I_reg] = chip8->V[target_v_reg] / 100;                //MSB
    chip8->ram[chip8->I_reg + 1] = (chip8->V[target_v_reg] / 100) % 10;
    chip8->ram[chip8->I_reg + 2] = (chip8->V[target_v_reg] % 100) % 10;     //LSB
    chip8->pc_reg += 2;
}

// Opcode FX55: Stores V0 to VX (including VX) in memory starting at address I. The offset from I is
//      increased by 1 for each value written, but I itself is left unmodified
void st_V_regs (Chip8 *chip8){
    uint8_t end_ld_v_reg = (chip8->current_op & 0X0F00) >> 8;
    int i =0;

    for (i = 0 ; i <= end_ld_v_reg ; i++) {
        chip8->ram[chip8->I_reg+1] = chip8->V[i];
    }

    chip8->pc_reg += 2;
}

// Opcode FX65: Fills V0 to VX (including VX) with values from memory starting at address I.
//      The offset from I is increased by 1 for each value written, but I itself is left unmodified.
void ld_V_regs (Chip8 *chip8){
    uint8_t end_ld_v_reg = (chip8->current_op & 0X0F00) >> 8;
    int i =0;

    for (i = 0 ; i <= end_ld_v_reg ; i++) {
        chip8->V[i] = chip8->ram[chip8->I_reg+1];
    }

    chip8->pc_reg += 2;
}
