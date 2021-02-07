#pragma once

struct registros{
    unsigned char A;
    unsigned char F;
    unsigned char B;
    unsigned char C;
    unsigned char D;
    unsigned char E;
    unsigned char H;
    unsigned char L;
	char16_t HL;
	char16_t BC;
	char16_t DE;
	char16_t AF;
    unsigned short SP;
    unsigned short PC;
    unsigned char flags;
}extern regist;

