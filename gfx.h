#pragma once

typedef enum COLOUR { WHITE,LIGHT,DARK,BLACK } COLOUR;

extern unsigned char SScreenData[160][144][3];

COLOUR getColour(unsigned char colourNum, unsigned short address);

void renderTiles();

void renderSprites();

void drawScanline();

void updateGfx(int cycles);

void setLCDStatus();

bool testBit(unsigned short address, int bit);

//int bitGetVal(unsigned char byte, int bit);

template< typename typeData >
typeData bitGetVal( typeData inData, size_t inBitPosition )
{
	typeData lMsk = 1 << inBitPosition ;
	return ( inData & lMsk ) ? 1 : 0 ;
}

unsigned char bitReset(unsigned char addr, int position);

unsigned char bitSet(unsigned char addr, int position);

bool isLCDEnabled();

void RequestInterupt(int bit);