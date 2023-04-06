#pragma once

extern unsigned char SRAM[8192];
extern unsigned char VRAM[8192];
extern unsigned char OAM[256];
extern unsigned char IO[256];
extern unsigned char cartucho[32768];
extern unsigned char switchRAM[8192];
extern unsigned char HRAM[128];

void DMATransfer(unsigned char a);
void writeMEMB(unsigned short dir, unsigned char a);
void writeMEM16(unsigned short dir, unsigned short a);
unsigned char loadMEMB(unsigned short dir);
unsigned short loadMEM16(unsigned short dir);
unsigned short loadMEM16pila(unsigned short *puntero);
void writeMEM16pila(unsigned short valor, unsigned short *puntero);