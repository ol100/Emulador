#include "cpu.h"
#include "registro.h"
#include "memoria.h"
#include "interrupciones.h"
#include <stdio.h>

unsigned char master=1;
unsigned char activado=0;
unsigned char flags=0;
unsigned char halto=0;
int m_DividerVariable=0;
int m_TimerVariable=0;
int m_CurrentClockSpeed=1024;

/*void vectorInterrupcion(){
	if(master==1 && loadMEMB(0xffff)==1){
		//vblank
		if(loadMEMB(0xFF0F) & 0x01){
			printf("INTERRUPCION VBLANK\n");
			writeMEMB(0xFF0F,(loadMEMB(0xFF0F) & 0xFE));
			vblankInterrupcion();
		}
		//lcdstat
		if(loadMEMB(0xFF0F) & 0x02){
			writeMEMB(0xFF0F,(loadMEMB(0xFF0F) & 0xFD));
			lcdstatInterrupcion();
		}
		//timer
		if(loadMEMB(0xFF0F) & 0x04){
			writeMEMB(0xFF0F,(loadMEMB(0xFF0F) & 0xFB));
			timerInterrupcion();
		}
		//serial
		if(loadMEMB(0xFF0F) & 0x08){
			writeMEMB(0xFF0F,(loadMEMB(0xFF0F) & 0xF7));
			serialInterrupcion();
		}
		//joypad
		if(loadMEMB(0xFF0F) & 0x10){
			writeMEMB(0xFF0F,(loadMEMB(0xFF0F) & 0xEF));
			joypadInterrupcion();
		}
	}
}*/

void vectorInterrupcion(){
	//comprobar que las interrupciones estan activadas
	if (master)//master==1
	{
		//Comprobar que hay interrupciones encoladas
		unsigned char requestFlag = loadMEMB(0xFF0F);
		if (requestFlag > 0)
		{
			//recorrerse los bits para ver que interrupciones estan activas
			for (int bit = 0; bit < 8; bit++)
			{
				if (TestBit(requestFlag, bit))
				{
					//Comprobar que se la interrupcion esta habilitada para ser ejecutada
					unsigned char enabledReg = loadMEMB(0xFFFF);
					if (TestBit(enabledReg,bit))
					{
						// yup it is enabled, so lets DOOOOO ITTTTT
						ServiceInterrupt(bit) ;
					}
				}
			}
		}
	}
}

void ServiceInterrupt(int num){
	writeMEM16pila(regist.PC,&regist.SP);
	halto = 0;//false
	printf("\n \n HALTO A 0 \n \n");

	switch(num)
	{
		case 0: regist.PC = 0x40 ; break ;// V-Blank
		case 1: regist.PC = 0x48 ; break ;// LCD-STATE
		case 2: regist.PC = 0x50 ; break ;// Timer
		case 4: regist.PC = 0x60 ; break ;// JoyPad
	}

	master = 0;
	writeMEMB(0xFF0F,(BitReset(loadMEMB(0xFF0F), num)));
}

static int timerhack = 0;

void Timer(int ciclos){
	unsigned char timerAtts = lecturadirecta(0xFF07);

	m_DividerVariable += ciclos;

	if (TestBit(timerAtts, 2))
	{
		m_TimerVariable += ciclos;

		// time to increment the timer
		if (m_TimerVariable >= m_CurrentClockSpeed)
		{
			m_TimerVariable = 0 ;
			bool overflow = false ;
			if (lecturadirecta(0xFF05) == 0xFF)
			{
				overflow = true ;
			}
			unsigned char temp1=lecturadirecta(0xFF05);
			temp1++;
			escrituradirecta(0xFF05,temp1);

			if (overflow)
			{
				timerhack++;

				escrituradirecta(0xFF05, lecturadirecta(0xFF06));
				
				unsigned char flags1= loadMEMB(0xff0f);
			    flags1= flags1 | 0x04;
			    writeMEMB(0xff0f,flags1);
			}
		}
	}

	// do divider register
	if (m_DividerVariable >= 256)
	{
		m_DividerVariable = 0;
		unsigned char temp2=lecturadirecta(0xFF04);
		temp2++;
		escrituradirecta(0xFF04,temp2);
	}
}




//el tratamiento de instrucciones desactiva las interrupciones y guarda PC en la pila

//Esta no se toca hasta saber como hacer cosas con SDL para mostrar las capas y colores
void vblankInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x40;
	
	//clock_cycle+=12;
}

void lcdstatInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x48;
	
	//clock_cycle+=12;
}

void timerInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x50;
	//clock_cycle+=12;
}

void serialInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x58;
	//clock_cycle+=12;
}

void joypadInterrupcion(){
	master=0;
	writeMEM16pila(regist.PC,&regist.SP);
	regist.PC= 0x60;
	//clock_cycle+=12;
}

void volverInterrupcion(){
	master = 1;
	regist.PC = loadMEM16pila(&regist.SP);
}

bool TestBit(unsigned short address, int bit)
{
    return ((address) & (1 << bit ));
}

unsigned char BitReset(unsigned char addr, int position)
{
    addr &= ~(1 << position);
    return addr;
}