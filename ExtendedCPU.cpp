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
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_a }//0x27
	
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

//0x21 SLA B 
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