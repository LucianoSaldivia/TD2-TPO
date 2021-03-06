
#include "main.h"
volatile extern uint8_t base_de_tiempo_timer;
// Load the rom into memory starting at location 0x200
void load_rom(Chip8 *chip8) {
    long rom_length;
  	FIL fp;
  	FRESULT res;
  	FATFS fs;
  	UINT datos_leidos;
  	DIR dp;
  	static FILINFO fno;
  	uint8_t tecla;

  	f_mount(&fs, "", 0);
  	res = f_opendir(&dp, "/");

    if (res == FR_OK) {
    	f_readdir(&dp, &fno); //Leo el directorio
			ST7920_SendString(0, 0, fno.fname);
    	while(1){

    		if(fno.fname[0] == 0)
    			f_rewinddir(&dp);
    		if (pase_por_systick){
    			tecla=Teclado();
    			pase_por_systick = 0;
    		}
    		else
    			buffKey = NO_KEY; // Ya lei y reseteo el buffer sino corre mas rapido el core que el systick
    		switch(tecla){
					case 2:
						ST7920_Clear();
						f_readdir(&dp, &fno); //Leo el directorio
						ST7920_SendString(0, 0, fno.fname);
						buffKey = NO_KEY;
					break;
					case 5:
						res = f_open(&fp, fno.fname, FA_READ);
						rom_length=f_size(&fp);
						f_read(&fp, &rom_buffer,  rom_length,&datos_leidos);
						if ((PROGRAM_END_ADDR - PROGRAM_START_ADDR) >= rom_length) {
							for(int i = 0; i < rom_length; i++) {
									chip8->ram[i + 0x200] = rom_buffer[i];
							}
						}
						ST7920_Clear();
						ST7920_GraphicMode(1); // Paso a modo grafico para mostrar la rom

				    f_closedir(&dp);
				    f_close(&fp);
				    return;
					break;
					case 8:
						f_rewinddir(&dp);
						buffKey = NO_KEY; // Ya lei y reseteo el buffer sino corre mas rapido el core que el systick
					break;
    		}
    	}
    }
}



/* 
* Initilize the system to its startup state, all of the 
* ram elements are set to 0, the stack is cleared, and the registers 
* are cleared. The PC register starts execution at location 0x200
* in memory
*/
void init_system(Chip8 *chip8) {

    chip8->pc_reg = PC_START;
    chip8->current_op = 0;
    chip8->sp_reg = 0;
    chip8->I_reg = 0;


    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            chip8->screen[i][j] = 0;
        }
    }


    for (int i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0;
    }


    for (int i = 0; i < TOTAL_RAM; i++) {
        chip8->ram[i] = 0;
    }


    for (int i = 0; i < NUM_V_REGISTERS; i++) {
        chip8->V[i] = 0;
    }


    for(int i = 0; i < FONTSET_SIZE; i++) {
        chip8->ram[i] = FONTSET[i];
    }

    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    base_de_tiempo_timer = 0;

    for (int i = 0; i < NUM_KEYS; i++) {
        chip8->keyboard[i] = FALSE;
    }
    chip8->was_key_pressed = FALSE;
}

// Largely similar to the init function, however all of the ram is not cleared 
// (so the rom does not have to be re-loaded into memory)
void reset_system(Chip8 *chip8) {
   /* chip8->is_running_flag = TRUE;
    chip8->draw_screen_flag = FALSE;
    chip8->is_paused_flag = FALSE;*/

    chip8->pc_reg = PC_START;
    chip8->current_op = 0;
    chip8->sp_reg = 0;
    chip8->I_reg = 0;

    // Clear display (memory)
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            chip8->screen[i][j] = 0;
        }
    }

    // Clear ram from the fontset end (80) to the Program ram 
    for (int i = 80; i < PROGRAM_START_ADDR; i++) {
        chip8->ram[i] = 0;
    }

    // Clear registers, keyboard and stack (all 16 each)
    for (int i = 0; i < 16; i++) {
        chip8->V[i] = 0;
        chip8->keyboard[i] = FALSE;
        chip8->stack[i] = 0;
    }
    // Reset timers to 0
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
}


/* 
* Fetches the next opcode to execute from memory which is
* located at the pc_reg and the pc_reg + 1 (opcode is 2 bytes)
*/
uint16_t fetch_opcode(Chip8 *chip8) {
    uint16_t opcode;
    uint8_t msB = chip8->ram[chip8->pc_reg];
    uint8_t lsB = chip8->ram[chip8->pc_reg + 1];

    opcode = msB << 8 | lsB;

    return opcode;
}


/* 
* Calls the instruction to execute based on the fetched opcode.
*
* If logging is enabled, the program will print the opcode and what
* instruction was ran.
*/
void execute_instruction( void *dps) {

	dummy_parameters * dp = (dummy_parameters *)dps;
	Chip8 *chip8 = dp->user_chip8_under_test;
	int logging = dp->logging;
		uint16_t opcode = fetch_opcode(chip8);
    chip8->current_op = opcode;

    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x00FF) {
                case 0x00E0:
                    if (logging) {printf("Instruction Clear screen (00E0)\n");}
                    cls(chip8);
                    break;

                case 0x00EE:
                    if (logging) {printf("Instruction Return from Subroutine (00EE)\n");}
                    return_from_subroutine(chip8);
                    break;

                default:
                    printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
                    exit(EXIT_FAILURE);
                }
                break;

        case 0x1000:
            if (logging) {printf("Instruction Jump (1NNN)\n");}
            jump(chip8);
            break;
        
        case 0x2000:
            if (logging) {printf("Instruction Call Subroutine (2NNN)\n");}
            call_subroutine(chip8);
            break;

        case 0x3000:
            if (logging) {printf("Skip next instr Vx == kk (3XKK)\n");}
            se_Vx_kk(chip8);
            break;

        case 0x4000:
            if (logging) {printf("Skip next instr Vx != kk (4XKK)\n");}
            sne_Vx_kk(chip8);
            break;
        
        case 0x5000:
            if (logging) {printf("Skip next instr Vx == Vy (5XY0)\n");}
            se_Vx_Vy(chip8);
            break;

        case 0x6000:
            if (logging) {printf("Instruction Load Vx reg (6XKK)\n");}
            ld_Vx(chip8);
            break;

        case 0x7000:
            if (logging) {printf("Instruction ADD Vx reg immediate (7XKK)\n");}
            add_Vx_imm(chip8);
            break;

        case 0x8000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    if (logging) {printf("Instruction Move Vy reg into Vx reg (8XY0)\n");}
                    move_Vx_Vy(chip8);
                    break;
                    
                case 0x0001:
                    if (logging) {printf("Instruction OR (8XY1)\n");}
                    or_Vx_Vy(chip8);
                    break;

                case 0x0002:
                    if (logging) {printf("Instruction AND (8XY2)\n");}
                    and_Vx_Vy(chip8);
                    break;

                case 0x0003:
                    if (logging) {printf("Instruction XOR (8XY3)\n");}
                    xor_Vx_Vy(chip8);
                    break;

                case 0x0004:
                    if (logging) {printf("Instruction ADD VX VY (8XY4)\n");}
                    add_Vx_Vy(chip8);
                    break;

                case 0x0005:
                    if (logging) {printf("Instruction SUB VX VY (8XY5)\n");}
                    sub_Vx_Vy(chip8);
                    break;

                case 0x0006:
                    if (logging) {printf("Instruction SHR VX (8XY6)\n");}
                    shr(chip8);
                    break;

                case 0x0007:
                    if (logging) {printf("Instruction SUBN VX VY (8XY7)\n");}
                    subn_Vx_Vy(chip8);
                    break;

                case 0x000E:
                    if (logging) {printf("Instruction SHL VX (8XYE)\n");}
                    shl(chip8);
                    break;

                default:
                    printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
                    exit(EXIT_FAILURE);
                }
                break;

        case 0x9000:
            if (logging) {printf("Skip next instr Vx != Vy (9XY0)\n");}
            sne_Vx_Vy(chip8);
            break;

        case 0xA000:
            if (logging) {printf("Instruction LDI (ANNN)\n");}
            ldi(chip8);
            break;

        case 0xB000:
            if (logging) {printf("Instruction JUMP + V0 (BNNN)\n");}
            jump_V0(chip8);
            break;

        case 0xC000:
            if (logging) {printf("Instruction RNG Vx (CXKK)\n");}
            rnd(chip8);
            break;

        case 0xD000:
            if (logging) {printf("Draw Sprite (DXYN)\n");}
            drw(chip8);
            break;

        case 0xE000:
            switch(opcode & 0x00FF) {
                case 0x009E:
                    if (logging) {printf("Instruction Skip next instr if key pressed (009E)\n");}
                    skp(chip8);
                    break;

                case 0x00A1:
                    if (logging) {printf("Instruction Skip next instr if key not pressed (00A1)\n");}
                    sknp(chip8);
                    break;

                default:
                    printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
                    exit(EXIT_FAILURE);
                }
                break;

        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007:
                    if (logging) {printf("Instruction Load VX with Delay Timer (0007)\n");}
                    ld_Vx_dt(chip8);
                    break;

                case 0x000A:
                    if (logging) {printf("Instruction Wait for key press (000A)\n");}
                    ld_Vx_k(chip8);
                    break;

                case 0x0015:
                    if (logging) {printf("Instruction Load Delay Timer with VX (0015)\n");}
                    ld_dt_Vx(chip8);
                    break;

                case 0x0018:
                    if (logging) {printf("Instruction Load SOUND Timer with VX (0018)\n");}
                    ld_st_Vx(chip8);
                    break;

                case 0x001E:
                    if (logging) {printf("Instruction ADD Index and Vx (001E)\n");}
                    add_i_Vx(chip8);
                    break;

                case 0x0029:
                    if (logging) {printf("Instruction LOAD Font from VX value (0029)\n");}
                    ld_F_Vx(chip8);
                    break;

                case 0x0033:
                    if (logging) {printf("Instruction STORE BCD of VX value (0033)\n");}
                    st_bcd_Vx(chip8);
                    break;

                case 0x0055:
                    if (logging) {printf("Instruction STORE Regs V[0] - V[X] starting at I register (0055)\n");}
                    st_V_regs(chip8);
                    break;

                case 0x0065:
                    if (logging) {printf("Instruction LOAD Regs V[0] - V[X] starting at I register (0065)\n");}
                    ld_V_regs(chip8);
                    break;

                default:
                    printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
                    exit(EXIT_FAILURE);
                }
                break;

        default:
            printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
            exit(EXIT_FAILURE);
    }
}



void process_user_input(void * dp) {
	Chip8 *chip8 = (Chip8*)dp;
	uint8_t tecla;
	DriverTeclado();
	tecla=Teclado();

	//Si la tecla presionada coincide con la que tengo en el array le pongo TRUE sino FALSE
	for ( uint8_t i = 0; i < NUM_KEYS; i++) {
		if (tecla== KEYMAP[i])
			chip8->keyboard[i] = TRUE;
		else
			chip8->keyboard[i] = FALSE;
	}
}


/* 
* Updates the system timers for the emulator
*
* If the delay_timer or the sound_timer are > 0
* the corrisponding timer is decremented by 1
*/
void update_timers(Chip8 *chip8) {
		// Increnmento una variable en 1 en el systick, 16ms aprox 60 Hz
		if (chip8->delay_timer > 0)
        chip8->delay_timer--;
    if (chip8->sound_timer > 0)
        chip8->sound_timer--;
}


/*****************************
* Debugging functions below
******************************/

void print_regs(Chip8 *chip8) {
    // print registers
    printf("Current OP: 0x%X\n", chip8->current_op);
    for (int i = 0; i < NUM_V_REGISTERS; i++) {
        printf("V Reg %X: 0x%X\n",i , chip8->V[i]);
    }
    printf("Index Reg: 0x%X\n", chip8->I_reg);
    printf("PC Reg: 0x%X\n", chip8->pc_reg);
    printf("SP Reg: 0x%X\n", chip8->sp_reg);
    printf("Delay Timer Reg: 0x%X\n", chip8->delay_timer);
    printf("Sound Timer Reg: 0x%X\n", chip8->sound_timer);
    printf("\n");
}


void print_stack(Chip8 *chip8) {
    // print stack
    for (int i = 0; i < STACK_SIZE; i++) {
        printf("Stack Element %i: 0x%X\n",i , chip8->stack[i]);
    }
}


void print_keyboard(Chip8 *chip8) {
    // print keyboard
    for (int i = 0; i < NUM_KEYS; i++) {
        printf("Keyboard Key %X: %i\n",i , chip8->keyboard[i]);
    }
}
