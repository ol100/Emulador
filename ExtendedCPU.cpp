#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "registro.h"
#include "memoria.h"
#include "ExtendedCPU.h"
#include "cpu.h"
using namespace std;

//aqui vienen las instrucciones CB
const struct CBinstruction CBinstructions[256]={
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_b },//0x00 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_c },//0x01
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_d },//0x02
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_e },//0x03
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_h },//0x04
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_l },//0x05
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:rlc_hl },//0x06
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_a },//0x07
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_b },//0x08 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_c },//0x09
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_d },//0x0a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_e },//0x0b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_h },//0x0c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_l },//0x0d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:rrc_hl },//0x0e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_a },//0x0f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_b },//0x10 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_c },//0x11
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_d },//0x12
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_e },//0x13
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_h },//0x14
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_l },//0x15
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:rl_hl },//0x16
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_a },//0x17
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_b },//0x18 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_c },//0x19
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_d },//0x1a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_e },//0x1b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_h },//0x1c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_l },//0x1d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:rr_hl },//0x1e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_a },//0x1f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_b },//0x20 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_c },//0x21
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_d },//0x22
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_e },//0x23
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_h },//0x24
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_l },//0x25
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:sla_hl },//0x26
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_a },//0x27
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_b },//0x28 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_c },//0x29
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_d },//0x2a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_e },//0x2b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_h },//0x2c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_l },//0x2d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:sra_hl },//0x2e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_a },//0x2f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_b },//0x30 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_c },//0x31
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_d },//0x32
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_e },//0x33
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_h },//0x34
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_l },//0x35
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:swap_hl },//0x36
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_a },//0x37
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_b },//0x38 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_c },//0x39
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_d },//0x3a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_e },//0x3b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_h },//0x3c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_l },//0x3d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:srl_hl },//0x3e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_a },//0x3f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_b },//0x40 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_c },//0x41
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_d },//0x42
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_e },//0x43
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_h },//0x44
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_l },//0x45
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:bit_0_hl },//0x46
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_a },//0x47
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_b },//0x48
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_c },//0x49
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_d },//0x4a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_e },//0x4b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_h },//0x4c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_l },//0x4d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:bit_1_hl },//0x4e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_a },//0x4f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_b },//0x50
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_c },//0x51
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_d },//0x52
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_e },//0x53
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_h },//0x54
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_l },//0x55
	{ valid_instruction:true, clock_cycle:16, machine_cycle:2, action:bit_2_hl },//0x56
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_a }//0x57
	
	};


static unsigned char rlc(unsigned char registro){
    unsigned char u = registro >> 7;
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro= registro << 1;
	//como es una rotacion, se le mete al final lo que "salio"
	registro += u;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
    if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }
	

    return registro;
}


static unsigned char rrc(unsigned char registro){
	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = registro & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro= registro >> 1;
	//como es una rotacion, se le mete por el otro lado lo que salio
	registro += u << 7;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
}

static unsigned char rl(unsigned char registro){
	//cogemos el valor del bit de carry
	unsigned char bit=regist.F & 0x10;
	bit= bit >>4;
	bit= bit & 0x01;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	//vemos si el mas significativo de A es 1 o 0
	unsigned char u = registro >> 7;
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro = registro << 1;

	//como es una rotacion, se le mete al final lo que "salio"
	registro += bit;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;

}

static unsigned char rr(unsigned char registro){
	//cogemos el valor del bit de carry
	unsigned char bit=regist.F & 0x10;
	bit= bit <<3;
	bit= bit & 0x80;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = registro & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro = registro >> 1;

	//como es una rotacion, se le mete al final lo que "salio"
	registro += bit;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;

}

static unsigned char sla(unsigned char registro){
    unsigned char u= registro >>7;
    if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}
    registro=registro<<1;

    regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
    
}

static unsigned char sra(unsigned char registro){
    unsigned char u= registro & 0x01;
	unsigned char bitquesaleyvuelve;
    if (u != 0){
		regist.F = regist.F | 0x10;
		bitquesaleyvuelve= 0x80;
	}else
	{
		regist.F= regist.F & 0xEF;
		bitquesaleyvuelve= 0x00;
	}
    registro=registro >> 1;
	registro= registro + bitquesaleyvuelve;


    regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
    
}

static unsigned char swap(unsigned char registro){
	unsigned char parte_baja=(registro & 0xF0)>> 4;
	unsigned char parte_alta=(registro & 0x0F)<< 4;
	registro= parte_baja | parte_alta;
	
	regist.F= regist.F & 0xEF;//desactiva carry
	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
}

static unsigned char srl(unsigned char registro){
    unsigned char u= registro & 0x01;
    if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}
    registro=registro >> 1;

    regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
    
}

static void bit(unsigned char bit, unsigned char registro){
	unsigned char u;
	if(bit==0x00){
		u=registro & 0x01;
	}else if(bit==0x01){
		u=registro & 0x02;
		u= u>>1;
	}else if(bit==0x02){
		u=registro & 0x04;
		u= u>>2;
	}else if(bit==0x03){
		u=registro & 0x08;
		u= u>>3;
	}else if(bit==0x04){
		u=registro & 0x10;
		u= u>>4;
	}else if(bit==0x05){
		u=registro & 0x20;
		u= u>>5;
	}else if(bit==0x06){
		u=registro & 0x40;
		u= u>>6;
	}else if(bit==0x07){
		u=registro & 0x80;
		u= u>>7;
	}
	if(u==0){
		regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }
	regist.F= regist.F & 0xBF;//desactiva el flag N
	regist.F= regist.F | 0x20;//activa el flag H

}

//0x00 RLC B
void rlc_b(void){
	regist.B=rlc(regist.B);
}

//0x01 RLC C
void rlc_c(void){
	regist.C=rlc(regist.C);
}

//0x02 RLC D
void rlc_d(void){
	regist.D=rlc(regist.D);
}

//0x03 RLC E
void rlc_e(void){
	regist.E=rlc(regist.E);
}

//0x04 RLC H
void rlc_h(void){
	regist.H=rlc(regist.H);
	deconstruirHL();
}

//0x05 RLC L
void rlc_l(void){
	regist.L=rlc(regist.L);
	deconstruirHL();
}

//0x06 RLC (HL)
void rlc_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rlc(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x07 RLC A
void rlc_a(void){
	regist.A=rlc(regist.A);
}

//0x08 RRC B
void rrc_b(void){
	regist.B=rrc(regist.B);
}

//0x09 RRC C
void rrc_c(void){
	regist.C=rrc(regist.C);
}

//0x0a RRC D
void rrc_d(void){
	regist.D=rrc(regist.D);
}

//0x0b RRC E
void rrc_e(void){
	regist.E=rrc(regist.E);
}

//0x0c RRC H
void rrc_h(void){
	regist.H=rrc(regist.H);
	deconstruirHL();
}

//0x0d RRC L
void rrc_l(void){
	regist.L=rrc(regist.L);
	deconstruirHL();
}

//0x0e RRC (HL)
void rrc_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rrc(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x0f RRC A
void rrc_a(void){
	regist.A=rrc(regist.A);
}

//0x10 RL B
void rl_b(void){
	regist.B=rl(regist.B);
}

//0x11 RL C
void rl_c(void){
	regist.C=rl(regist.C);
}

//0x12 RL D
void rl_d(void){
	regist.D=rl(regist.D);
}

//0x13 RL E
void rl_e(void){
	regist.E=rl(regist.E);
}

//0x14 RL H
void rl_h(void){
	regist.H=rl(regist.H);
	deconstruirHL();
}

//0x15 RL L 
void rl_l(void){
	regist.L=rl(regist.L);
	deconstruirHL();
}

//0x16 RL (HL)
void rl_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rl(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x17 RL A 
void rl_a(void){
	regist.A=rl(regist.A);
}

//0x18 RR B 
void rr_b(void){
	regist.B=rr(regist.B);
}

//0x19 RR C 
void rr_c(void){
	regist.C=rr(regist.C);
}

//0x1a RR D 
void rr_d(void){
	regist.D=rr(regist.D);
}

//0x1b RR E 
void rr_e(void){
	regist.E=rr(regist.E);
}

//0x1c RR H 
void rr_h(void){
	regist.H=rl(regist.H);
	deconstruirHL();
}

//0x1d RR L 
void rr_l(void){
	regist.L=rl(regist.L);
	deconstruirHL();
}

//0x1e RR (HL)
void rr_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rr(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x1f RR A 
void rr_a(void){
	regist.A=rr(regist.A);
}

//0x20 SLA B 
void sla_b(void){
	regist.B=sla(regist.B);
}

//0x21 SLA C 
void sla_c(void){
	regist.C=sla(regist.C);
}

//0x22 SLA D 
void sla_d(void){
	regist.D=sla(regist.D);
}

//0x23 SLA E 
void sla_e(void){
	regist.E=sla(regist.E);
}

//0x24 SLA H 
void sla_h(void){
	regist.H=sla(regist.H);
	deconstruirHL();
}

//0x25 SLA L 
void sla_l(void){
	regist.L=sla(regist.L);
	deconstruirHL();
}

//0x26 SLA (HL)
void sla_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=sla(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x27 SLA A 
void sla_a(void){
	regist.A=sla(regist.A);
}

//0x28 SRA B 
void sra_b(void){
	regist.B=sra(regist.B);
}

//0x29 SRA C 
void sra_c(void){
	regist.C=sra(regist.C);
}

//0x2a SRA D 
void sra_d(void){
	regist.D=sra(regist.D);
}

//0x2b SRA E 
void sra_e(void){
	regist.E=sra(regist.E);
}

//0x2c SRA H 
void sra_h(void){
	regist.H=sra(regist.H);
	deconstruirHL();
}

//0x2d SRA L 
void sra_l(void){
	regist.L=sra(regist.L);
	deconstruirHL();
}

//0x2e SRA (HL)
void sra_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=sra(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x2f SRA A 
void sra_a(void){
	regist.A=sra(regist.A);
}

//0x30 SWAP B 
void swap_b(void){
	regist.B=swap(regist.B);
}

//0x31 SWAP C 
void swap_c(void){
	regist.C=swap(regist.C);
}

//0x32 SWAP D 
void swap_d(void){
	regist.D=swap(regist.D);
}

//0x33 SWAP E 
void swap_e(void){
	regist.E=swap(regist.E);
}

//0x34 SWAP H 
void swap_h(void){
	regist.H=swap(regist.H);
	deconstruirHL();
}

//0x35 SWAP L 
void swap_l(void){
	regist.L=swap(regist.L);
	deconstruirHL();
}

//0x36 SWAP (HL)
void swap_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=swap(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x37 SWAP A 
void swap_a(void){
	regist.A=swap(regist.A);
}

//0x38 SRL B 
void srl_b(void){
	regist.B=srl(regist.B);
}

//0x39 SRL C 
void srl_c(void){
	regist.C=srl(regist.C);
}

//0x3a SRL D 
void srl_d(void){
	regist.D=srl(regist.D);
}

//0x3b SRL E 
void srl_e(void){
	regist.E=srl(regist.E);
}

//0x3c SRL H 
void srl_h(void){
	regist.H=srl(regist.H);
	deconstruirHL();
}

//0x3d SRL L 
void srl_l(void){
	regist.L=srl(regist.L);
	deconstruirHL();
}

//0x3e SRL (HL)
void srl_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=srl(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x3f SRL A 
void srl_a(void){
	regist.A=srl(regist.A);
}

//0x40 BIT 0,B
void bit_0_b(void){
	bit(0x00,regist.B);
}

//0x41 BIT 0,C
void bit_0_c(void){
	bit(0x00,regist.C);
}

//0x42 BIT 0,D
void bit_0_d(void){
	bit(0x00,regist.D);
}

//0x43 BIT 0,E
void bit_0_e(void){
	bit(0x00,regist.E);
}

//0x44 BIT 0,H
void bit_0_h(void){
	bit(0x00,regist.H);
}

//0x45 BIT 0,L
void bit_0_l(void){
	bit(0x00,regist.L);
}

//0x46 BIT 0,(HL)
void bit_0_hl(void){
	reconstruirHL();
	bit(0x00,loadMEMB(regist.HL));
}

//0x47 BIT 0,A
void bit_0_a(void){
	bit(0x00,regist.A);
}

//0x48 BIT 1,B
void bit_1_b(void){
	bit(0x01,regist.B);
}

//0x49 BIT 1,C
void bit_1_c(void){
	bit(0x01,regist.C);
}

//0x4a BIT 1,D
void bit_1_d(void){
	bit(0x01,regist.D);
}

//0x4b BIT 1,E
void bit_1_e(void){
	bit(0x01,regist.E);
}

//0x4c BIT 1,H
void bit_1_h(void){
	bit(0x01,regist.H);
}

//0x4d BIT 1,L
void bit_1_l(void){
	bit(0x01,regist.L);
}

//0x4e BIT 1,(HL)
void bit_1_hl(void){
	reconstruirHL();
	bit(0x01,loadMEMB(regist.HL));
}

//0x4f BIT 1,A
void bit_1_a(void){
	bit(0x01,regist.A);
}

//0x50 BIT 2,B
void bit_2_b(void){
	bit(0x02,regist.B);
}

//0x51 BIT 2,C
void bit_2_c(void){
	bit(0x02,regist.C);
}

//0x52 BIT 2,D
void bit_2_d(void){
	bit(0x02,regist.D);
}

//0x53 BIT 2,E
void bit_2_e(void){
	bit(0x02,regist.E);
}

//0x54 BIT 2,H
void bit_2_h(void){
	bit(0x02,regist.H);
}

//0x55 BIT 2,L
void bit_2_l(void){
	bit(0x02,regist.L);
}

//0x56 BIT 2,(HL)
void bit_2_hl(void){
	reconstruirHL();
	bit(0x02,loadMEMB(regist.HL));
}

//0x57 BIT 2,A
void bit_2_a(void){
	bit(0x02,regist.A);
}