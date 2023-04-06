#include "cpu.h"
#include "memoria.h"
#include "interrupciones.h"
#include "ppu.h"
#include "graphics.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

unsigned char scanline=0;
unsigned char lcdStatus=0;
unsigned char control=0;
unsigned char windowY=0;
unsigned char windowX=0;
unsigned char scrollX=0;
unsigned char scrollY=0;
/*
int m_scanlineCounter=456;

void ejecutarPPU(int ciclos){
	
	setLCDStatus();
	if(isLCDEnabled()){
		m_scanlineCounter -= ciclos;
		//std::cout<<"M_SCANLINECOUNTER:"<<(int)m_scanlineCounter<<std::endl;
	}else{
		return;
	}
	
	if(m_scanlineCounter<=0){
		unsigned char temp=loadMEMB(0xFF44);
		temp++;
		writeMEMB(0xFF44,temp);
		unsigned char scanline1 = loadMEMB(0xFF44);
		std::cout<<"SCANLINE:"<<(int)scanline1<<std::endl;
		
		m_scanlineCounter=456;
		
		if(scanline1==144){
			flags= flags | 0x01;// activa la interrucion vblank
		}
		else if(scanline1>153){
			writeMEMB(0xFF44,0);
		}
		else if(scanline1<144){
			//std::cout<<"SCANLINE < 144"<<std::endl;
			//dibujarScanline();
		}
		
	}
}

void setLCDStatus(){
	unsigned char status=loadMEMB(0xFF41);
	if(false == isLCDEnabled()){
		m_scanlineCounter = 456;
		writeMEMB(0xFF44,0);
		status &= 252;
        status = set_bit(status, 0);
		writeMEMB(0xFF41, status);
		return;
	}
	
	unsigned char current_line = loadMEMB(0xFF44);
	unsigned char currentmode = status & 0x3;
	unsigned char mode=0;
	bool reqInt= false;
	
	if(current_line >=144){
		mode=1;
		status= status | 0x01; //bit 0
		status= status & 0xFD; //bit 1
		reqInt = TestBit(status,4);
	}
	else{
		int mode2bounds = 456 -80;
		int mode3bounds = mode2bounds - 172;
		
		//mode 2
		if(m_scanlineCounter>=mode2bounds){
			mode=2;
			status= status | 0x02; //bit 1
			status= status & 0xFE; //bit 0 
			reqInt = TestBit(status,4);
		}
		//mode 3
		else if(m_scanlineCounter>=mode3bounds){
			mode=3;
			status= status | 0x01; //bit 0
			status= status | 0x02; //bit 1
		}
		//mode 0
		else{
			mode=0;
			status= status & 0xFE; //bit 0 
			status= status & 0xFD; //bit 1
			reqInt = TestBit(status,4);
		}
	}
	
	writeMEMB(0xff41,status);
	if (reqInt && (mode != currentmode)){flags= flags | 0x02;}
	//AQUI VA LA COINCIDENCIA DE REGISTROS
}

bool isLCDEnabled(){
	/*unsigned char test= control & 0x80;
	test = test >> 7;
	if(test==1){
		std::cout<<"TRUE"<<std::endl;
		return true;
	}else{
		return false;
	}
	return TestBit(loadMEMB(0xFF40),7) ;
}

unsigned char set_bit(unsigned char addr, int position)
{
    addr |= 1 << position;
    return addr;
}*/