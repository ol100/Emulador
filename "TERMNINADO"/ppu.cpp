#include "cpu.h"
#include "memoria.h"
#include "interrupciones.h"
#include "ppu.h"
#include "graphics.h"

unsigned char scanline=0;
unsigned char lcdStatus;
unsigned char control;
unsigned char windowY;
unsigned char windowX;
unsigned char scrollX;
unsigned char scrollY;

int m_scanlineCounter=0;

void ejecutarPPU(){
	
	setLCDStatus();
	if(isLCDEnabled()){
		m_scanlineCounter -= clock_cycle;
	}else{
		return;
	}
	
	if(m_scanlineCounter<=0){
		scanline++;
		
		m_scanlineCounter=456;
		
		if(scanline==144){
			flags= flags | 0x01;// activa la interrucion vblank
		}
		else if(scanline>153){
			scanline=0;
		}
		else if(scanline<144){
			dibujarScanline();
		}
		
	}
}

void setLCDStatus(){
	if(false == isLCDEnabled()){
		m_scanlineCounter = 456;
		scanline=0;
		lcdStatus= lcdStatus & 0xFC;
		lcdStatus= lcdStatus | 0x01;
		return;
	}
	
	unsigned char currentmode = lcdStatus & 0x3;
	unsigned char mode=0;
	bool reqInt= false;
	
	if(scanline >=144){
		mode=1;
		lcdStatus= lcdStatus | 0x01; //bit 0
		lcdStatus= lcdStatus & 0xFD; //bit 1
		unsigned char bit4= (lcdStatus & 0x10) >>4;
		if(bit4 == 1){reqInt=true;}
		else{reqInt=false;}
	}
	else{
		int mode2bounds = 456 -80;
		int mode3bounds = mode2bounds - 172;
		
		//mode 2
		if(m_scanlineCounter>=mode2bounds){
			mode=2;
			lcdStatus= lcdStatus | 0x02; //bit 1
			lcdStatus= lcdStatus & 0xFE; //bit 0 
			unsigned char bit5= (lcdStatus & 0x20) >>5;
			if(bit5 == 1){reqInt=true;}
			else{reqInt=false;}
		}
		//mode 3
		else if(m_scanlineCounter>=mode3bounds){
			mode=3;
			lcdStatus= lcdStatus | 0x01; //bit 0
			lcdStatus= lcdStatus | 0x02; //bit 1
		}
		//mode 0
		else{
			mode=0;
			lcdStatus= lcdStatus & 0xFE; //bit 0 
			lcdStatus= lcdStatus & 0xFD; //bit 1
			unsigned char bit3= (lcdStatus & 0x08) >>3;
			if(bit3 == 1){reqInt=true;}
			else{reqInt=false;}
		}
	}
	
	if (reqInt && (mode != currentmode)){flags= flags | 0x02;}
	//AQUI VA LA COINCIDENCIA DE REGISTROS
}

bool isLCDEnabled(){
	unsigned char test= control & 0x80;
	test = test >> 7;
	if(test==1){
		return true;
	}else{
		return false;
	}
}