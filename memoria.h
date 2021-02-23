#pragma once

extern unsigned char SRAM[8192];
extern unsigned char VRAM[8192];
extern unsigned char OAM[256];
extern unsigned char IO[256];
extern unsigned char cartucho[32768];
extern unsigned char switchRAM[8192];
extern unsigned char HRAM[128];


void writeMEMB(char16_t dir, unsigned char a);
void writeMEM16(char16_t dir, char16_t a);
unsigned char loadMEMB(unsigned short dir);
unsigned short loadMEM16(unsigned short dir);
char16_t loadMEM16pila(unsigned short *puntero);
void writeMEM16pila(char16_t valor, unsigned short *puntero);