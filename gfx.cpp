#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "memoria.h"
#include <iostream>
#include <assert.h>

int SScanlineCounter=456;
unsigned char SScreenData[160][144][3];

COLOUR getColour(unsigned char colourNum, unsigned short address) {
  COLOUR res = WHITE;
  unsigned char  palette = loadMEMB( address);
  int hi = 0;
  int lo = 0;

  //which bits of the colour palette does the colour id map to?
  switch (colourNum) {
  case 0: hi = 1; lo = 0; break;
  case 1: hi = 3; lo = 2; break;
  case 2: hi = 5; lo = 4; break;
  case 3: hi = 7; lo = 6; break;
  default: assert(false) ; break ;
  }

  //use the palette to get the colour
  int colour = 0;
  colour = bitGetVal(palette, hi) << 1;
  colour |= bitGetVal(palette, lo);

  //convert the game colour to emultor colour
  switch (colour) {
  case 0: res = WHITE; break;
  case 1: res = LIGHT; break;
  case 2: res = DARK; break;
  case 3: res = BLACK; break;
  default: assert(false) ; break ;
  }

  return res;
}


void renderTiles() {
  unsigned short tileData = 0;
  unsigned short backgroundMemory = 0;
  bool unsig = true;

  //where to draw the visual area and the window
  unsigned char  scrollY = loadMEMB( 0xFF42);
  unsigned char  scrollX = loadMEMB( 0xFF43);
  unsigned char windowY = loadMEMB( 0xFF4A);
  unsigned char windowX = loadMEMB( 0xFF4B) - 7;
  unsigned char lcdControl = loadMEMB( 0xFF40);
  bool usingWindow = false;

  //is the window enabled?
  if (testBit(lcdControl,5)) {
      //is the current scanline we're drawing
      //within the windows Y pos?
      if (windowY <= loadMEMB( 0xFF44) ) {
		usingWindow = true;
      }

    }

    //which tile data are we using?
    if (testBit(lcdControl,4)) {
      tileData = 0x8000;
    }

    else {
      //IMPORTANT: this memory region uses signed
      //unsigned chars as tile identifiers
      tileData = 0x8800;
      unsig = false;
    }

    //which background mem?
    if (usingWindow == false) {
      if (testBit(lcdControl,3)) {
		backgroundMemory = 0x9C00;
      }
      else {
		backgroundMemory = 0x9800;
      }
    }

    else {
      //which window memory?
      if (testBit(lcdControl,6)) {
		backgroundMemory = 0x9C00;
      }
      else {
		backgroundMemory = 0x9800;
      }
    }

    unsigned char yPos = 0;

    //yPos is used to calculate which of 32 vertical tiles the
    //current scanline is drawing

    if (!usingWindow)
      yPos = scrollY + loadMEMB( 0xFF44);
    else
      yPos = loadMEMB( 0xFF44) - windowY;


    //which of the 8 vertical pixels of the current
    //tile is the scanline on?
    unsigned short tileRow = (((unsigned char)(yPos/8)) *32);

    //time to start drawing the 160 horizontal pixels
    //for this scanline
    for (int pixel = 0; pixel < 160; pixel++) {
      unsigned char xPos = pixel + scrollX;

      //translate the current x pos to window space if necessary
      if (usingWindow) {
		if (pixel >= windowX) {
		  xPos = pixel -windowX;
		}
      }

      //which of the 32 horizontal tiles does this xPos fall within?
      unsigned short tileCol = (xPos/8);
      signed short tileNum;

      //get the tile identity number. Remember it can be signed
      //or unsigned
      unsigned short tileAddress = backgroundMemory + tileRow + tileCol;
      if (unsig)
		tileNum = (unsigned char)loadMEMB(tileAddress);
      else
		tileNum = (signed char)loadMEMB(tileAddress);

      //deduce where this tile identifier is in memory.
      unsigned short tileLocation = tileData;

      if (unsig)
		tileLocation += (tileNum *16);
      else
		tileLocation += ((tileNum + 128) *16);

      //find the correct vertical line we're on of the
      //tile to get the tile data
      //from memory
      unsigned char line = yPos % 8;
      line *= 2; //each vertical line takes up two unsigned chars in memory
      unsigned char data1 = loadMEMB( tileLocation + line);
      unsigned char data2 = loadMEMB( tileLocation + line + 1);

      //pixel 0 in the tile is bit 7 of data1 and data2
      //Pixel 1 is bit 6 etc
      int colourBit = xPos % 8;
      colourBit -= 7;
      colourBit *= -1;

      //combine data 2 and data 1 to get colour id for this pixel
      //in the tile
      int colourNum = bitGetVal(data2, colourBit);
      colourNum <<= 1;
      colourNum |= bitGetVal(data1, colourBit);

      //now we have the colour id get the actual
      //colour from palette 0xFF47
      COLOUR col = getColour(colourNum, 0xFF47);
      int red = 0;
      int green = 0;
      int blue = 0;

      //setup RGB values
      switch(col){
		  case WHITE: red = 255; green = 255; blue = 255; break;
		  case LIGHT: red = 0xCC; green = 0xCC; blue = 0xCC; break;
		  case DARK: red = 0x77; green = 0x77; blue = 0x77; break;
      }

      int finaly = loadMEMB(0xFF44);

      //safety check to make sure what im about
      //to set is in the 160x144 bounds
      if ((finaly < 0) || (finaly >143) || (pixel < 0) || (pixel > 159)) {
		continue;
      }

      SScreenData[pixel][finaly][0] = red;
	  //std::cout<<"ROJO: "<<SScreenData[pixel][finaly][0]<<std::endl;
      SScreenData[pixel][finaly][1] = green;
      SScreenData[pixel][finaly][2] = blue;

    }
	
	//FILE *f = fopen("tile1.bin", "wb");
	//fwrite(SScreenData, 4096, 1, f);
	//fclose(f);

}

/*void renderTiles()
{
	unsigned char lcdControl = loadMEMB( 0xFF40);
	// lets draw the background (however it does need to be enabled)
	if (testBit(lcdControl, 0))
	{
		unsigned short tileData = 0 ;
		unsigned short backgroundMemory =0 ;
		bool unsig = true ;

		unsigned char scrollY = loadMEMB(0xFF42) ;
		unsigned char scrollX = loadMEMB(0xFF43) ;
		unsigned char windowY = loadMEMB(0xFF4A) ;
		unsigned char windowX = loadMEMB(0xFF4B) - 7;

		bool usingWindow = false ;

		if (testBit(lcdControl,5))
		{
			if (windowY <= loadMEMB(0xFF44))
				usingWindow = true ;
		}
		else
		{
			usingWindow = false ;
		}

		// which tile data are we using?
		if (testBit(lcdControl,4))
		{
			tileData = 0x8000 ;
		}
		else
		{
			tileData = 0x8800 ;
			unsig= false ;
		}

		// which background mem?
		if (false == usingWindow)
		{
			if (testBit(lcdControl,3))
				backgroundMemory = 0x9C00 ;
			else
				backgroundMemory = 0x9800 ;
		}
		else
		{
			if (testBit(lcdControl,6))
				backgroundMemory = 0x9C00 ;
			else
				backgroundMemory = 0x9800 ;
		}


		unsigned char yPos = 0 ;

		if (!usingWindow)
			yPos = scrollY + loadMEMB(0xFF44) ;
		else
			yPos = loadMEMB(0xFF44) - windowY;

		unsigned short tileRow = (((unsigned char)(yPos/8))*32) ;

		for (int pixel = 0 ; pixel < 160; pixel++)
		{
			unsigned char xPos = pixel+scrollX ;

			if (usingWindow)
			{
				if (pixel >= windowX)
				{
					xPos = pixel - windowX ;
				}
			}

			unsigned short tileCol = (xPos/8) ;
			signed short tileNum ;

			if(unsig)
				tileNum = (unsigned char)loadMEMB(backgroundMemory+tileRow + tileCol) ;
			else
				tileNum = (signed char)loadMEMB(backgroundMemory+tileRow + tileCol) ;

			unsigned short tileLocation = tileData ;

			if (unsig)
				tileLocation += (tileNum * 16) ;
			else
				tileLocation += ((tileNum+128) *16) ;

			unsigned char line = yPos % 8 ;
			line *= 2;
			unsigned char data1 = loadMEMB(tileLocation + line) ;
			//printf("TILE LOCATION: %d\n",tileLocation);
			//printf("DATA 1: %d\n",data1);
			unsigned char data2 = loadMEMB(tileLocation + line + 1) ;

			int colourBit = xPos % 8 ;
			colourBit -= 7 ;
			colourBit *= -1 ;

			int colourNum = bitGetVal(data2,colourBit) ;
			colourNum <<= 1;
			colourNum |= bitGetVal(data1,colourBit) ;

			COLOUR col = getColour(colourNum, 0xFF47) ;
			//printf("COLOR OBTENIDO: %d\n", col);
			int red = 0;
			int green = 0;
			int blue = 0;

			switch(col)
			{
			case WHITE:	red = 255; green = 255 ; blue = 255; break ;
			case LIGHT:red = 0xCC; green = 0xCC ; blue = 0xCC; break ;
			case DARK:	red = 0x77; green = 0x77 ; blue = 0x77; break ;
			}

			int finaly = loadMEMB(0xFF44) ;

			if ((finaly < 0) || (finaly > 143) || (pixel < 0) || (pixel > 159))
			{
				//assert(false);
				continue ;
			}

			SScreenData[pixel][finaly][0] = red ;
			SScreenData[pixel][finaly][1] = green ;
			SScreenData[pixel][finaly][2] = blue ;
		}
	}
	//FILE *f = fopen("tile1.bin", "wb");
	//fwrite(SScreenData, 8192, 1, f);
	//fclose(f);
}*/


void renderSprites() {
  unsigned char lcdControl = loadMEMB( 0xFF40);
  bool use8x16 = false;
  if (testBit(lcdControl,2)) {
    use8x16 = true;
  }

  for (int sprite = 0; sprite < 40; sprite++) {
    //sprite occupies 4 unsigned chars in the sprite attributes table
    unsigned char index = sprite * 4;
    unsigned char yPos = loadMEMB( 0xFE00 + index) - 16;
    unsigned char xPos = loadMEMB( 0xFE00 + index + 1) - 8;
    unsigned char tileLocation = loadMEMB( 0xFE00 + index + 2);
    unsigned char attributes  = loadMEMB( 0xFE00 + index + 3);

    bool yFlip = testBit(attributes,6);
    bool xFlip = testBit(attributes,5);

    int scanline = loadMEMB( 0xFF44);

    int ysize = 8;
    if (use8x16)
      ysize = 16;

    //does this sprite intercept with the scanline?
    if ((scanline >= yPos) && (scanline < (yPos +ysize))) {
	int line = scanline - yPos;

	//read the sprite in backwards in the y axis
	if (yFlip) {
	  line -= ysize;
	  line *= -1;
	}

	line *= 2; //same as for tiles
	unsigned short dataAddress = (0x8000 + (tileLocation * 16)) + line;
	unsigned char data1 = loadMEMB( dataAddress);
	unsigned char data2 = loadMEMB( dataAddress + 1);

	//its easier to read in from right to left as pixel 0 is
	//bit 7 in the colour data, pixel 1 is bit 6 etc
	for (int tilePixel = 7; tilePixel >= 0; tilePixel --) {
	  int colourbit = tilePixel;
	  // read the sprite in backwards for the x axis
	  if (xFlip) {
	    colourbit -= 7;
	    colourbit *= -1;
	  }

	  //the rest is the same as for tiles
	  int colourNum = bitGetVal(data2, colourbit);
	  colourNum <<= 1;
	  colourNum |=bitGetVal(data1, colourbit);

	  unsigned short colourAddress = testBit(attributes,4) ? 0xFF49:0xFF48;
	  COLOUR col = getColour(colourNum, colourAddress);

	  //white is transparent for sprites.
	  if (col == WHITE)
	    continue;


	  int red = 0;
	  int green = 0;
	  int blue = 0;

	  switch(col){
	  case WHITE: red = 255; green = 255; blue = 255; break;
	  case LIGHT: red = 0xCC; green = 0xCC; blue = 0xCC; break;
	  case DARK: red = 0x77; green = 0x77; blue = 0x77; break;
	  }

	  int xPix = 0 - tilePixel;
	  xPix += 7;

	  int pixel = xPos +xPix;

	  //sanity check
	  if ((scanline < 0) || (scanline >143) || (pixel < 0) || (pixel > 159)) {
	    continue;
	  }
	  
		 /* // check if pixel is hidden behind background
		if (testBit(attributes, 7) == 1)
		{
			if ( (SScreenData[scanline][pixel][0] != 255) || (SScreenData[scanline][pixel][1] != 255) || (SScreenData[scanline][pixel][2] != 255) )
				continue ;
		}*/

		SScreenData[pixel][scanline][0] = red;
		SScreenData[pixel][scanline][1] = green;
		SScreenData[pixel][scanline][2] = blue;

	}
      }
	}

}


/*void renderSprites() {
	unsigned char lcdControl = loadMEMB( 0xFF40);
	// lets draw the sprites (however it does need to be enabled)

	if (testBit(lcdControl, 1))
	{
		bool use8x16 = false ;
		if (testBit(lcdControl,2))
			use8x16 = true ;

		for (int sprite = 0 ; sprite < 40; sprite++)
		{
 			unsigned char index = sprite*4 ;
 			unsigned char yPos = loadMEMB(0xFE00+index) - 16;
 			unsigned char xPos = loadMEMB(0xFE00+index+1)-8;
 			unsigned char tileLocation = loadMEMB(0xFE00+index+2) ;
 			unsigned char attributes = loadMEMB(0xFE00+index+3) ;
			//printf("ATTRIBUTES: %d\n", attributes);

			bool yFlip = testBit(attributes,6) ;
			bool xFlip = testBit(attributes,5) ;

			int scanline = loadMEMB(0xFF44);

			int ysize = 8;

			if (use8x16)
				ysize = 16;

 			if ((scanline >= yPos) && (scanline < (yPos+ysize)))
 			{
 				int line = scanline - yPos ;

 				if (yFlip)
 				{
 					line -= ysize ;
 					line *= -1 ;
 				}

 				line *= 2;
 				unsigned char data1 = loadMEMB( (0x8000 + (tileLocation * 16)) + line ) ;
 				unsigned char data2 = loadMEMB( (0x8000 + (tileLocation * 16)) + line+1 ) ;



 				for (int tilePixel = 7; tilePixel >= 0; tilePixel--)
 				{
					int colourbit = tilePixel ;
 					if (xFlip)
 					{
 						colourbit -= 7 ;
 						colourbit *= -1 ;
 					}
 					int colourNum = bitGetVal(data2,colourbit) ;
 					colourNum <<= 1;
 					colourNum |= bitGetVal(data1,colourbit) ;

					COLOUR col = getColour(colourNum, testBit(attributes,4)?0xFF49:0xFF48) ;

 					// white is transparent for sprites.
 					if (col == WHITE)
 						continue ;

 					int red = 0;
 					int green = 0;
 					int blue = 0;

					switch(col)
					{
					case WHITE:	red = 255; green = 255 ; blue = 255; break ;
					case LIGHT:red = 0xCC; green = 0xCC ; blue = 0xCC; break ;
					case DARK:	red = 0x77; green = 0x77 ; blue = 0x77; break ;
					}

 					int xPix = 0 - tilePixel ;
 					xPix += 7 ;

					int pixel = xPos+xPix ;

					if ((scanline < 0) || (scanline > 143) || (pixel < 0) || (pixel > 159))
					{
					//	assert(false) ;
						continue ;
					}

					// check if pixel is hidden behind background
					if (testBit(attributes, 7) == 1)
					{
						if ( (SScreenData[scanline][pixel][0] != 255) || (SScreenData[scanline][pixel][1] != 255) || (SScreenData[scanline][pixel][2] != 255) )
							continue ;
					}

 					SScreenData[scanline][pixel][0] = red ;
 					SScreenData[scanline][pixel][1] = green ;
 					SScreenData[scanline][pixel][2] = blue ;

 				}
 			}
		}
	}
}*/

void drawScanline() {
  unsigned char control = loadMEMB(0xFF40);
  if (testBit(control,0)) {
	//printf("RENDER TILES\n");
    renderTiles();
  }

  if (testBit(control,1)) {
	//printf("RENDER SPRITES\n");
    renderSprites();
  }
  /*if(testBit(control,7)){
	  renderTiles();
	  renderSprites();
  }*/
}




void updateGfx(int cycles) {
  setLCDStatus();

  if (isLCDEnabled()) {
    SScanlineCounter -= cycles;
  } else{
	if(loadMEMB(0xFF44)>153){
		escrituradirecta(0xFF44,0);
	}
	return;
  }

  if (SScanlineCounter <= 0) {
    unsigned char temp=loadMEMB(0xFF44);
	temp++;
	escrituradirecta(0xFF44,temp);
    unsigned char currentScanline = loadMEMB(0xFF44);
	//printf("SCANLINE %d \n",currentScanline);

    SScanlineCounter = 456;

    if (currentScanline == 144) {
       //flags= flags | 0x01;
	   unsigned char flagso= loadMEMB(0xff0f);
	   flagso= flagso | 0x01;
	   writeMEMB(0xff0f,flagso);
    }

    else if (currentScanline > 153) {
		escrituradirecta(0xFF44,0);
    }

    else if (currentScanline < 144) {
      drawScanline();
    }
  }
}

void setLCDStatus() {

  unsigned char status = loadMEMB(0xFF41);
  if (!isLCDEnabled()) {

	//printf("LCD APAGADO \n");

    //set the mode to 1 during lcd disabled and reset scanlineCounter
    SScanlineCounter = 456;
    escrituradirecta(0xFF44,0);
    status &= 252; //reset bit 0 and 1
    //status = bitSet(status, 0);
	//status |= 0x80;
	status = bitSet(status, 0);
    writeMEMB(0xFF41, status);
    return;

  }


  unsigned char currentline = loadMEMB(0xFF44);
  unsigned char currentmode = loadMEMB(0xFF41) & 0x3;

  unsigned char mode = 0;
  bool reqInterupt = false;

  //if vblank so set mode to 1
  if (currentline >= 144){
      mode = 1;
      status = bitSet(status,0);
      status = bitReset(status,1);
      reqInterupt = testBit(status,4);
  }
  else {

    int mode2bounds = 456 - 80;
    int mode3bounds = mode2bounds - 172;


    //mode 2
    if (SScanlineCounter >= mode2bounds) {
      mode = 2;
      status = bitSet(status,1);
      status = bitReset(status,0);
      reqInterupt = testBit(status,5);

    }
    //mode 3
    else if (SScanlineCounter >= mode3bounds) {
      mode = 3;
      status = bitSet(status,1);
      status = bitSet(status,0);

    }

    //mode 0
    else {
      mode = 0;
      status = bitReset(status,1);
      status = bitReset(status,0);
      reqInterupt = testBit(status,3);

    }

  }


  //just entered a new mode so request interupt

  if (reqInterupt && (mode !=currentmode)) {
    RequestInterupt(1);
  }

  //check coincident flag

  if (loadMEMB(0xFF44) == loadMEMB(0xFF45)) {
    status = bitSet(status, 2);

    if ( testBit(status, 6) )
      RequestInterupt(1);

  } else {
    status = bitReset(status,2);
  }
  status |= 0x80;
  writeMEMB(0xFF41,status);

}

bool testBit(unsigned short address, int bit)
{
    return ((address) & (1 << bit ));
}

/*int bitGetVal(unsigned char byte, int bit){
	 return (byte >> bit) & 1;
}*/

unsigned char bitReset(unsigned char addr, int position)
{
    addr &= ~(1 << position);
    return addr;
}


unsigned char bitSet(unsigned char addr, int position)
{
    addr |= 1 << position;
    return addr;
}

bool isLCDEnabled() {
  return testBit(loadMEMB(0xFF40), 7);
}

void RequestInterupt(int bit)
{
	unsigned char requestFlag = loadMEMB(0xFF0F);
	requestFlag = bitSet(requestFlag,bit);
	writeMEMB(0xFF0F, requestFlag);
}