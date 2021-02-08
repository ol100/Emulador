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
const struct CBinstruction CBinstructions[256]={{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:rst_38h }};


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