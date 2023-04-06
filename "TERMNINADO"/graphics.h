#pragma once



enum COLOUR {WHITE=0, LIGHT_GRAY=1, DARK_GRAY=2, BLACK=3};

extern unsigned char m_ScreenData[160][144][3];
	
//extern const COLOUR palette[4];
int BitGetVal(unsigned char byte, int bit);
void dibujarScanline();
void renderTiles();
COLOUR GetColour(unsigned char colourNum, unsigned short address);
void RenderSprites();
bool TestBit(unsigned short address, int bit);