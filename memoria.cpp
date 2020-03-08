#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>

using namespace std;

unsigned char SRAM[8192];
unsigned char VRAM[8192];
unsigned char OAM[256];
unsigned char IO[256];
unsigned char cartucho[32768];
unsigned char switchRAM[8192];
unsigned char HRAM[128];

void writeMEMB(char16_t dir, unsigned char a){
    SRAM[dir]=a;
}

void writeMEM16(char16_t dir, char16_t a){
    unsigned char bajo= (unsigned char)(a & 0xFF);
    char16_t temp= a>>8;
    unsigned char alto= (unsigned char)(temp & 0xFF);
    SRAM[dir]= bajo;
    SRAM[dir +1]= alto;


}

unsigned char loadMEMB(char16_t dir){
    return SRAM[dir];
}

char16_t loadMEM16(char16_t dir){
    char16_t patata= loadMEMB(dir);
    patata= patata<<8;
    patata= loadMEMB(dir + 1)<<8 | patata; //es little endian
    return patata;
}