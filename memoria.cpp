#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "memoria.h"

using namespace std;

unsigned char SRAM[8192];
unsigned char VRAM[8192];
unsigned char OAM[256];
unsigned char IO[256];
unsigned char cartucho[32768];
unsigned char switchRAM[8192];
unsigned char HRAM[128];

void writeMEMB(char16_t dir, unsigned char a){
    //SRAM[dir]=a;
    if(dir >= 0xa000 && dir <= 0xbfff)
		SRAM[dir - 0xa000] = a;
	
	else if(dir >= 0x8000 && dir <= 0x9fff) {
		VRAM[dir - 0x8000] = a;
//actualizar la vram conlleva que algo cambia en la pantalla, habria que actualizar la pantalla aqui
	}

	if(dir >= 0xc000 && dir <= 0xdfff)
		SRAM[dir - 0xc000] = a;
	
	else if(dir >= 0xe000 && dir <= 0xfdff)
		SRAM[dir - 0xe000] = a;
	
	else if(dir >= 0xfe00 && dir <= 0xfeff)
		OAM[dir - 0xfe00] = a;
	
	else if(dir >= 0xff80 && dir <= 0xfffe)
		HRAM[dir - 0xff80] = a;
}

void writeMEM16(char16_t dir, char16_t a){
    unsigned char bajo= (unsigned char)(a & 0xFF);
    char16_t temp= a>>8;
    unsigned char alto= (unsigned char)(temp & 0xFF);
    writeMEMB(dir,bajo);
    writeMEMB(dir+1,alto);

}

unsigned char loadMEMB(char16_t dir){
    if(dir <=0x7fff){
        return cartucho[dir];
    }
    else if(dir >= 0x8000 && dir<=0x9fff){
        return VRAM[dir- 0x8000];
    }
    else if(dir >=0xa000 && dir<=0xbfff){
        return switchRAM[dir-0xa000];
    }else if(dir >= 0xc000 && dir<=0xdfff){
        return SRAM[dir- 0xc000];
    }else if(dir >=0xe000 && dir<=0xfdff){
        return SRAM[dir-0xe000];
    }else if(dir >=0xFE00 && dir<=0xfeff){
        return OAM[dir-0xfe00];
    }
    //return SRAM[dir-0xfe00];
}

char16_t loadMEM16(char16_t dir){ //porque llamaria a estas variables patata, ahora el javi del futuro no sabe que hacia la funcion
    char16_t patata= loadMEMB(dir);
    patata= patata<<8;
    patata= loadMEMB(dir + 1)<<8 | patata; //es little endian
    return patata;
}

char16_t loadMEM16pila(unsigned short *puntero){
    char16_t cargado= loadMEM16(*puntero);
    *puntero+=2;
    return cargado;
}

void writeMEM16pila(char16_t valor, unsigned short *puntero){
    *puntero-=2;
    writeMEM16((char16_t) *puntero, valor);
}