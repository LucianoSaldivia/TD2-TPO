
#include "main.h"

volatile extern uint8_t base_de_tiempo_timer;
void fallo (uint8_t codigo_falla){
	char codigo = codigo_falla + '0';
	ST7920_Clear();
	ST7920_SendString(0, 0, "CODIGO FALLA");
	ST7920_SendString(2, 2,&codigo);
}
uint8_t mi_rand(void){
	uint8_t seed = 7;
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
void load_rom(Chip8 *chip8) {
    long rom_length;
  	FIL fp;
  	FRESULT res;
  	FATFS fs;
  	UINT datos_leidos;
  	DIR dp;
  	static FILINFO fno;
  	uint8_t tecla,teclas,flag;

  	f_mount(&fs, "", 0);
  	res = f_opendir(&dp, "/");
  	pase_por_systick = 0;
    if (res == FR_OK) {
    	f_readdir(&dp, &fno); //Leo el directorio
			ST7920_SendString(0, 0, fno.fname);
    	while(1){

    		if(fno.fname[0] == 0)
    			f_rewinddir(&dp);
    		//if (pase_por_systick&&(buffKey == NO_KEY)){
    		/*if (flag){
    			teclas = Teclado();
    			flag = 0;
    		}

    		if (tecla == NO_KEY)
    			flag = 1;*/
    		/*	pase_por_systick=0;
    		}
    		else
    			buffKey = NO_KEY;*/
    		tecla = Teclado();
    		if (tecla == NO_KEY)
    			flag = 1;
    		switch(tecla){
					case 2:
						if (flag)
						{
							flag = 0;
							ST7920_Clear();
							f_readdir(&dp, &fno); //Leo el directorio
							ST7920_SendString(0, 0, fno.fname);
						}

					break;
					case 5:
						res = f_open(&fp, fno.fname, FA_READ);
						rom_length=f_size(&fp);
						f_read(&fp, &rom_buffer,  rom_length,&datos_leidos);
						if ((PROGRAM_END_ADDR - PROGRAM_START_ADDR) >= rom_length) {

							//Cargo la rom a partir de 0x200
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
					break;
    		}
    	}
    }
}



/* 
* Inicializo las variables en 0
*/
void init_system(Chip8 *chip8) {

    chip8->pc_reg = PC_START;
    chip8->current_op = 0;
    chip8->sp_reg = 0;
    chip8->I_reg = 0;

    //PANTALLA
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++)
            chip8->screen[i][j] = 0;
    }
    //STACK
    for (int i = 0; i < STACK_SIZE; i++)
        chip8->stack[i] = 0;
    //RAM
    for (int i = 0; i < TOTAL_RAM; i++)
        chip8->ram[i] = 0;
    //REGISTROS
    for (int i = 0; i < NUM_V_REGISTERS; i++)
        chip8->V[i] = 0;
    //Inicializo la fuente
    for(int i = 0; i < FONTSET_SIZE; i++)
        chip8->ram[i] = FONTSET[i];
    //Sonido
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    base_de_tiempo_timer = 0;
    //Teclado
    for (int i = 0; i < NUM_KEYS; i++)
        chip8->keyboard[i] = FALSE;

    chip8->was_key_pressed = FALSE;
}

/* 
* Busco el opcode, parte baja y alta
*/
uint16_t fetch_opcode(Chip8 *chip8) {
    uint16_t opcode;
    uint8_t msB = chip8->ram[chip8->pc_reg];
    uint8_t lsB = chip8->ram[chip8->pc_reg + 1];
    //Obtengo la parte alta y baja y lo recompongo
    opcode = msB << 8 | lsB;
    return opcode;
}



void exec_instruction(Chip8 *chip8) {
		//Hago un fetch del opcode para saber que instruccion ejecutar
    uint16_t opcode = fetch_opcode(chip8);

    chip8->current_op = opcode;

    switch(opcode & 0xF000) {
        case 0x0000:
					switch(opcode & 0x00FF) {
						case 0x00E0:
							cls(chip8);
							break;
						case 0x00EE:
							volver_subroutina(chip8);
							break;
						default:
							fallo(1);
					}
					break;
        case 0x1000:
					jump(chip8);
					break;
        case 0x2000:
					call_subroutina(chip8);
					break;
        case 0x3000:
					se_Vx_kk(chip8);
					break;
        case 0x4000:
					sne_Vx_kk(chip8);
					break;
        case 0x5000:
					se_Vx_Vy(chip8);
					break;
        case 0x6000:
					ld_Vx(chip8);
					break;
        case 0x7000:
					add_Vx_imm(chip8);
					break;
        case 0x8000:
					switch(opcode & 0x000F) {
						case 0x0000:
								move_Vx_Vy(chip8);
								break;
						case 0x0001:
								or_Vx_Vy(chip8);
								break;
						case 0x0002:
								and_Vx_Vy(chip8);
								break;
						case 0x0003:
								xor_Vx_Vy(chip8);
								break;
						case 0x0004:
								add_Vx_Vy(chip8);
								break;
						case 0x0005:
								sub_Vx_Vy(chip8);
								break;
						case 0x0006:
								shr(chip8);
								break;
						case 0x0007:
								subn_Vx_Vy(chip8);
								break;
						case 0x000E:
								shl(chip8);
								break;
						default:
								fallo(2);
					}
					break;
        case 0x9000:
					sne_Vx_Vy(chip8);
					break;
        case 0xA000:
					ldi(chip8);
					break;
        case 0xB000:
					jump_V0(chip8);
					break;
        case 0xC000:
					rnd(chip8);
					break;
        case 0xD000:
					drw(chip8);
					break;
        case 0xE000:
					switch(opcode & 0x00FF)
					{
							case 0x009E:
									skp(chip8);
									break;
							case 0x00A1:
									sknp(chip8);
									break;
							default:
									fallo(3);
					 }
					 break;

        case 0xF000:
					switch(opcode & 0x00FF)
					{
						case 0x0007:
							ld_Vx_dt(chip8);
							break;
						case 0x000A:
							ld_Vx_k(chip8);
							break;
						case 0x0015:
							ld_dt_Vx(chip8);
							break;
						case 0x0018:
							ld_st_Vx(chip8);
							break;
						case 0x001E:
							add_i_Vx(chip8);
							break;
						case 0x0029:
							ld_F_Vx(chip8);
							break;
						case 0x0033:
							st_bcd_Vx(chip8);
							break;
						case 0x0055:
							st_V_regs(chip8);
							break;
						case 0x0065:
							ld_V_regs(chip8);
							break;
						default:
							fallo(4);
					}
					break;
        default:
            fallo(5);
    }
}



void process_user_input(Chip8 *chip8) {

	uint8_t tecla;
	DriverTeclado();
	tecla=Teclado();
	//Si la tecla presionada coincide con la que tengo en el array le pongo TRUE sino FALSE
	for (int i = 0; i < NUM_KEYS; i++) {
		if (tecla== KEYMAP[i])
			chip8->keyboard[i] = TRUE;
		else
			chip8->keyboard[i] = FALSE;
	}
}


/* 
	Si la cuenta llega a 0 prendo el buzzer
*/
void update_timers(Chip8 *chip8) {
		// Increnmento una variable en 1 en el systick, 16ms aprox 60 Hz
		if (chip8->delay_timer > 0)
        chip8->delay_timer--;
    if (chip8->sound_timer > 0)
        chip8->sound_timer--;
}


