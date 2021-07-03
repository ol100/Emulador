#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include <assert.h>
#include "memoria.h"
#include "interrupciones.h"
#include "ppu.h"
#include "graphics.h"
#include "registro.h"
#include "keys.h"

using namespace std;

unsigned char SRAM[8192];
unsigned char VRAM[8192];
unsigned char OAM[256];
unsigned char IO[256];
unsigned char cartucho[32768];
unsigned char switchRAM[8192];
unsigned char HRAM[128];
unsigned char ff04=0;
unsigned char ff05=0;
unsigned char ff06=0;
unsigned char ff07=0;

void DMATransfer(unsigned char a){
	//printf("DMA DE LA LORAAAAJAGKJDHAGKJHADGKJHADGKJHADGJLHADGLJHYADGLJ AAAA AAAA AA");
	unsigned short dirrr = a<<8;
	for(int i=0;i< 0xA0; i++){
		writeMEMB(0xfe00+i, loadMEMB(dirrr+i));
	}
}

void writeMEMB(unsigned short dir, unsigned char a){
    //SRAM[dir]=a;
    if(dir >= 0xa000 && dir <= 0xbfff)
		SRAM[dir - 0xa000] = a;
	
	else if(dir >= 0x8000 && dir <= 0x9fff) {
		VRAM[dir - 0x8000] = a;
//actualizar la vram conlleva que algo cambia en la pantalla, habria que actualizar la pantalla aqui
	}

	if(dir >= 0xc000 && dir <= 0xdfff)
		switchRAM[dir - 0xc000] = a;
	
	else if(dir >= 0xe000 && dir <= 0xfdff)
		switchRAM[dir - 0xe000] = a;
	
	else if(dir >= 0xfe00 && dir <= 0xfeff)
		OAM[dir - 0xfe00] = a;
		
	
	
	else if(dir >= 0xff80 && dir <= 0xfffe)
		HRAM[dir - 0xff80] = a;
		
	else if(dir == 0xff04){
		ff04=0;
		m_DividerVariable=0;
	}
	else if(dir == 0xff05){ff05=a;}
	else if(dir == 0xff06){ff06=a;}
	else if(dir == 0xff07){
		printf("ME HE METIDO EN FF07 AAGAGAGFFFFFFFFFFFFFFFFGJFFGFFFGFGFFFFFFFG FGFG ");
		ff07=a;
		int timerVal = a & 0x03 ;

		int clockSpeed = 0 ;

		switch(timerVal)
		{
			case 0: clockSpeed = 1024 ; break ;
			case 1: clockSpeed = 16; break ;
			case 2: clockSpeed = 64 ;break ;
			case 3: clockSpeed = 256 ;break ; // 256
			default: assert(false); break ; // weird timer val
		}

		if (clockSpeed != m_CurrentClockSpeed)
		{
			m_TimerVariable = 0 ;
			m_CurrentClockSpeed = clockSpeed ;
		}
	}
	else if(dir == 0xff40){control=a;}
	else if(dir == 0xff41){lcdStatus=a;}
	else if(dir == 0xff42){scrollY=a;}
	else if(dir == 0xff43){scrollX=a;}
	else if(dir == 0xff44){scanline=0;}
    else if(dir == 0xff46){
		DMATransfer(a);
		IO[dir-0xff00]=a;
	}	
	else if(dir == 0xff0f){flags= a;}
	else if(dir >= 0xff00 && dir <= 0xff7f){
		if (dir == 0xFF00) // Joypad register
        {
			
			/*printf("VALOR PREVIO EN IO %d \n",IO[dir- 0xff00]);
			a = (a & 0xF0) | (IO[dir - 0xff00] & 0x0F);
			printf("VALOR GUARDADO EN IO %d \n",a);
            IO[dir- 0xff00] = a;*/
		 /*unsigned char bit4 = (a >> 4) & 0b00000001;
		 unsigned char bit5 = (a >> 5) & 0b00000001;
		 unsigned char reg = IO[dir - 0xff00];
		 if (bit4) {
			 reg &= ~(1U << 4);
		 }
		 else {
			 reg |= (1U << 4);
		 }
		 if (bit5) {
			 reg &= ~(1U << 5);
		 }
		 else {
			 reg |= (1U << 5);
		 }*/
		 printf("VALOR GUARDADO EN IO %d \n", a);
		 IO[dir - 0xff00] = a;
        }else{
			IO[dir - 0xff00] = a;
		}
	}
	
	else if(dir == 0xffff){activado = a;}
}

void writeMEM16(unsigned short dir, unsigned short a){
    /*unsigned char bajo= (unsigned char)(a & 0x00FF);
    //unsigned short temp= a>>8;
    unsigned char alto= (unsigned char)(a & 0xFF00);
	alto = alto>>8;
    writeMEMB(dir,bajo);
    writeMEMB(dir+1,alto);*/
	writeMEMB(dir, (unsigned char)(a & 0x00ff));
	writeMEMB(dir + 1, (unsigned char)((a & 0xff00) >> 8));

}

unsigned char loadMEMB(unsigned short dir){
    if(dir <=0x7fff){
        //printf("\n Direciion memoria: %d\n", cartucho[dir]);
        return cartucho[dir];
    }
    else if(dir >= 0x8000 && dir<=0x9fff){
        return VRAM[dir- 0x8000];
    }
    else if(dir >=0xa000 && dir<=0xbfff){
        return SRAM[dir-0xa000];
    }
	else if(dir >= 0xc000 && dir<=0xdfff){
        return switchRAM[dir- 0xc000];
    }
	else if(dir >=0xe000 && dir<=0xfdff){
        return switchRAM[dir-0xe000];
    }
	else if(dir >=0xFE00 && dir<=0xfeff){
        return OAM[dir-0xfe00];
    }
	
	
	else if(dir == 0xff40){return control;}
	else if(dir == 0xff41){return lcdStatus;}
	else if(dir == 0xff42){return scrollY;}
	else if(dir == 0xff43){return scrollX;}
    else if(dir == 0xff44){return scanline;}
	else if(dir == 0xff04) return (unsigned char)rand();// esto es un hack para ahorrarse implementar el timer y que funcione el tetris
	//else if(dir == 0xff04){return ff04;}
	else if(dir == 0xff05){return ff05;}
	else if(dir == 0xff06){return ff06;}
	else if(dir == 0xff07){return ff07;}
	else if(dir == 0xff0f){return flags;}
	else if(dir == 0xffff){return activado;}
	
	else if(dir >= 0xff80 && dir <= 0xfffe)
		return HRAM[dir - 0xff80];
	
	/*else if(dir == 0xff00) {
		if(!(IO[0x00] & 0x20)) {
			return (unsigned char)(0xc0 | keys.keys1 | 0x10);
		}
		
		else if(!(IO[0x00] & 0x10)) {
			return (unsigned char)(0xc0 | keys.keys2 | 0x20);
		}
		
		else if(!(IO[0x00] & 0x30)) return 0xff;
		else return 0;
	}*/
	else if(dir == 0xff00){return GetJoypadState();}
	else if(dir > 0xff00 && dir <= 0xff7f){
		return IO[dir- 0xff00];
	}
}

unsigned short loadMEM16(unsigned short dir){ //porque llamaria a estas variables patata, ahora el javi del futuro no sabe que hacia la funcion
    /*unsigned short patata= loadMEMB(dir);
    patata= patata;
    patata= loadMEMB(dir + 1)<<8 | patata; 
    return patata;*/
	unsigned short patata=loadMEMB(dir) | (loadMEMB(dir + 1) << 8);
	printf("VALOR RECUPERADO DE MEMORIA %d \n",patata);
    return loadMEMB(dir) | (loadMEMB(dir + 1) << 8);
}

unsigned short loadMEM16pila(unsigned short *puntero){
    unsigned short cargado= loadMEM16(regist.SP);
	printf("VALOR RECUPERADO DE PILA %d \n",cargado);
    //*puntero+=2;
	regist.SP= regist.SP + 2;
    return cargado;
}

void writeMEM16pila(unsigned short valor, unsigned short *puntero){
    regist.SP= regist.SP - 2;
	printf("VALOR GUARDADO EN PILA %d \n",valor);
	if(valor==57){
		printf("REGISTRO PC %d \n",regist.PC);
	}
    writeMEM16(regist.SP, valor);
}

unsigned char lecturadirecta(unsigned short dir){
	if(dir == 0xff40){return control;}
	else if(dir == 0xff04){return ff04;}
	else if(dir == 0xff05){return ff05;}
	else if(dir == 0xff06){return ff06;}
	else if(dir == 0xff07){return ff07;}
	else if(dir == 0xff41){return lcdStatus;}
	else if(dir == 0xff44){return scanline;}
	else if(dir == 0xff0f){return flags;}
	else if(dir == 0xffff){return activado;}
}

void escrituradirecta(unsigned short dir, unsigned char a){
	if(dir == 0xff40){control=a;}
	else if(dir == 0xff04){ff04=a;}
	else if(dir == 0xff05){ff05=a;}
	else if(dir == 0xff06){ff06=a;}
	else if(dir == 0xff07){ff07=a;}
	else if(dir == 0xff41){lcdStatus=a;}
	else if(dir == 0xff44){scanline=a;}
	else if(dir == 0xff0f){flags=a;}
	else if(dir == 0xffff){activado=a;}
}