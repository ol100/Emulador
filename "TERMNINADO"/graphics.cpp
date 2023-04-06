#include "graphics.h"
#include "interrupciones.h"
#include "memoria.h"
#include "ppu.h"

/*const COLOUR palette[4] = {
		{ 255, 255, 255 },
		{ 192, 192, 192 },
		{ 96, 96, 96 },
		{ 0, 0, 0 },
	};*/
	
unsigned char m_ScreenData[160][144][3];
	
//COLOUR framebuffer[160 * 144];

void dibujarScanline(){
	unsigned char bitcontrol0=control & 0x01;
	unsigned char bitcontrol1=(control & 0x02)>>1;
	if(bitcontrol0==1){
		renderTiles();
	}
	if(bitcontrol1==1){
		//renderSprites()
	}
}

int BitGetVal(unsigned char byte, int bit){
	 return (byte >> bit) & 1;
}

void renderTiles(){
	unsigned short tileData=0;
	unsigned short backgroundMemory=0;
	bool unsig = true;
	
	bool usingWindow= false;
	unsigned char bitcontrol5=(control & 0x20)>>5;
	if(bitcontrol5==1){
		if(windowY<=scanline){
			usingWindow=true;
		}
	}
	unsigned char bitcontrol4=(control & 0x10)>>4;
	if(bitcontrol4==1){
		tileData=0x8000;
	}
	else{
		tileData=0x8800;
		unsig=true;
	}
	
	unsigned char bitcontrol3=(control & 0x08)>>3;
	unsigned char bitcontrol6=(control & 0x40)>>6;
	if(false==usingWindow){
		if(bitcontrol3==1){
			backgroundMemory= 0x9c00;
		}
		else{
			backgroundMemory=0x9800;
		}
	}
	else{
		if(bitcontrol6==1){
			backgroundMemory=0x9c00;
		}
		else{
			backgroundMemory=0x9800;
		}
	}
	
	unsigned char yPos=0;
	
	if(!usingWindow){
		yPos=scrollY + scanline;
	}else{
		yPos= scanline - windowY;
	}
	
	unsigned short tileRow = ((yPos/8))*32;
	
	for(int i=0;i<160;i++){
		unsigned char xPos= i + scrollX;
		if(usingWindow){
			if(i>=windowX){
				xPos= i - windowX;
			}
		}
		
		unsigned short tileCol= (xPos/8);
		short tileNum;
		
		unsigned short tileAddrss=  backgroundMemory+tileRow+tileCol;
		if(unsig){
			tileNum=(unsigned char) loadMEMB(tileAddrss); //creo que es loadMEMB16
		}else{
			tileNum=(char) loadMEMB(tileAddrss);
		}
		
		unsigned short tileLocation = tileData ;

		if (unsig)
			tileLocation += (tileNum * 16);
		else
			tileLocation += ((tileNum+128) *16);
			
		unsigned char line = yPos%8;
		line *= 2;
		unsigned char data1 = loadMEMB(tileLocation+line);
		unsigned char data2 = loadMEMB(tileLocation + line + 1);
		
		int colourBit = xPos % 8 ;
		colourBit -= 7 ;
		colourBit *= -1 ;
		
		int colourNum = BitGetVal(data2,colourBit);
		colourNum <<= 1;
		colourNum |= BitGetVal(data1,colourBit);
		
		COLOUR col = GetColour(colourNum, 0xFF47) ;
		int red = 0;
		int green = 0;
		int blue = 0;
		
		switch(col)
		{
			case WHITE: red = 255; green = 255 ; blue = 255; break ;
			case LIGHT_GRAY:red = 0xCC; green = 0xCC ; blue = 0xCC; break ;
			case DARK_GRAY: red = 0x77; green = 0x77 ; blue = 0x77; break ;
		}
		
		int finaly = loadMEMB(0xFF44);
		
		if ((finaly<0)||(finaly>143)||(i<0)||(i>159))
		{
			continue ;
		}
		m_ScreenData[i][finaly][0] = red ;
		m_ScreenData[i][finaly][1] = green ;
		m_ScreenData[i][finaly][2] = blue ;
		
	}
}

COLOUR GetColour(unsigned char colourNum, unsigned short address)
{
   COLOUR res = WHITE ;
   unsigned char palette = loadMEMB(address) ;
   int hi = 0 ;
   int lo = 0 ;

   // which bits of the colour palette does the colour id map to?
   switch (colourNum)
   {
     case 0: hi = 1 ; lo = 0 ;break ;
     case 1: hi = 3 ; lo = 2 ;break ;
     case 2: hi = 5 ; lo = 4 ;break ;
     case 3: hi = 7 ; lo = 6 ;break ;
   }

   // use the palette to get the colour
   int colour = 0;
   colour = BitGetVal(palette, hi) << 1;
   colour |= BitGetVal(palette, lo) ;

   // convert the game colour to emulator colour
   switch (colour)
   {
     case 0: res = WHITE ;break ;
     case 1: res = LIGHT_GRAY ;break ;
     case 2: res = DARK_GRAY ;break ;
     case 3: res = BLACK ;break ;
   }

   return res ;
}

void RenderSprites()
{
   bool use8x16 = false ;
   unsigned char bitcontrol2=(control & 0x04)>>2;
   if (bitcontrol2==1){
	   use8x16 = true;
   }
   for (int sprite = 0 ; sprite < 40; sprite++)
   {
     // sprite occupies 4 bytes in the sprite attributes table
     unsigned char index = sprite*4 ;
     unsigned char yPos = loadMEMB(0xFE00+index) - 16;
     unsigned char xPos = loadMEMB(0xFE00+index+1)-8;
     unsigned char tileLocation = loadMEMB(0xFE00+index+2) ;
     unsigned char attributes = loadMEMB(0xFE00+index+3) ;

     bool yFlip = TestBit(attributes,6) ;
     bool xFlip = TestBit(attributes,5) ;

     int scanline = loadMEMB(0xFF44);

     int ysize = 8;
     if (use8x16)
       ysize = 16;

     // does this sprite intercept with the scanline?
     if ((scanline >= yPos) && (scanline < (yPos+ysize)))
     {
       int line = scanline - yPos ;

       // read the sprite in backwards in the y axis
       if (yFlip)
       {
         line -= ysize ;
         line *= -1 ;
       }

       line *= 2; // same as for tiles
       unsigned short dataAddress = (0x8000 + (tileLocation * 16)) + line ;
       unsigned char data1 = loadMEMB( dataAddress ) ;
       unsigned char data2 = loadMEMB( dataAddress +1 ) ;

       // its easier to read in from right to left as pixel 0 is
       // bit 7 in the colour data, pixel 1 is bit 6 etc...
       for (int tilePixel = 7; tilePixel >= 0; tilePixel--)
       {
         int colourbit = tilePixel;
         // read the sprite in backwards for the x axis
         if (xFlip)
         {
           colourbit -= 7 ;
           colourbit *= -1 ;
         }

         // the rest is the same as for tiles
         int colourNum = BitGetVal(data2,colourbit) ;
         colourNum <<= 1;
         colourNum |= BitGetVal(data1,colourbit) ;

         unsigned short colourAddress = TestBit(attributes,4)?0xFF49:0xFF48 ;
         COLOUR col=GetColour(colourNum, colourAddress ) ;

         // white is transparent for sprites.
         if (col == WHITE)
           continue ;

         int red = 0;
         int green = 0;
         int blue = 0;

         switch(col)
         {
           case WHITE: red =255;green=255;blue=255;break ;
           case LIGHT_GRAY:red =0xCC;green=0xCC ;blue=0xCC;break ;
           case DARK_GRAY:red=0x77;green=0x77;blue=0x77;break ;
         }

         int xPix = 0 - tilePixel ;
         xPix += 7 ;

         int pixel = xPos+xPix ;

         // sanity check
         if ((scanline<0)||(scanline>143)||(pixel<0)||(pixel>159))
         {
           continue ;
         }

         m_ScreenData[pixel][scanline][0] = red ;
         m_ScreenData[pixel][scanline][1] = green ;
         m_ScreenData[pixel][scanline][2] = blue ;
       }
     }
   }
}

bool TestBit(unsigned short address, int bit)
{
    return ((address) & (1 << bit ));
}