#include "cpu.h"
#include "registro.h"
#include "memoria.h"
#include "interrupciones.h"

unsigned char master;
unsigned char activado;
unsigned char flags;

void vectorInterrupcion(){
	if(master==1 && activado==1){
		//vblank
		if(flags & 0x01){
			flags = flags & 0xFE;
			vblankInterrupcion();
		}
		//lcdstat
		if(flags & 0x02){
			flags = flags & 0xFD;
			lcdstatInterrupcion();
		}
		//timer
		if(flags & 0x04){
			flags = flags & 0xFB;
			timerInterrupcion();
		}
		//serial
		if(flags & 0x08){
			flags = flags & 0xF7;
			serialInterrupcion();
		}
		//joypad
		if(flags & 0x10){
			flags = flags & 0xEF;
			joypadInterrupcion();
		}
	}
}

//el tratamiento de instrucciones desactiva las interrupciones y guarda PC en la pila

//Esta no se toca hasta saber como hacer cosas con SDL para mostrar las capas y colores
void vblankInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x40;
}

void lcdstatInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x48;
}

void timerInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x50;
}

void serialInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x58;
}

void joypadInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x60;
}

void volverInterrupcion(){
	master = 1;
	regist.PC = loadMEM16pila(&regist.SP);
}