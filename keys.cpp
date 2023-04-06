#include <stdio.h>
#include "keys.h"
#include "gfx.h"
#include "memoria.h"

unsigned char m_JoypadState=0xFF;

void KeyPressed(int key){
	bool previouslyUnset = false ;

	// if setting from 1 to 0 we may have to request an interupt
	if (testBit(m_JoypadState, key)==false)
	 previouslyUnset = true ;

	// remember if a keypressed its bit is 0 not 1
	m_JoypadState = bitReset(m_JoypadState, key) ;

	// button pressed
	bool button = true ;

	// is this a standard button or a directional button?
	if (key > 3)
	 button = true ;
	else // directional button pressed
	 button = false ;

	unsigned char keyReq =IO[0];
	bool requestInterupt = false ;

	// only request interupt if the button just pressed is
	// the style of button the game is interested in
	if (button && !testBit(keyReq,5))
	 requestInterupt = true ;

	// same as above but for directional button
	else if (!button && !testBit(keyReq,4))
	 requestInterupt = true ;

	// request interupt
	//if (requestInterupt && !previouslyUnset)
	 //RequestInterupt(4) ;
}

void KeyReleased(int key)
{
   m_JoypadState = bitSet(m_JoypadState,key) ;
}

unsigned char keys = 0xFF;

unsigned char GetJoypadState()
{
   unsigned char res = IO[0];
   // flip all the bits
   res ^= 0xFF ;

   // are we interested in the standard buttons?
   if (!testBit(res, 4))
   {
	 //printf("ME METO EN 1\n");
     unsigned char topJoypad = m_JoypadState >> 4 ;
     topJoypad |= 0xF0 ; // turn the top 4 bits on
     res &= topJoypad ; // show what buttons are pressed
   }
   else if (!testBit(res,5))//directional buttons
   {
	   //printf("ME METO EN 2\n");
     unsigned char bottomJoypad = m_JoypadState & 0xF ;
     bottomJoypad |= 0xF0 ;
     res &= bottomJoypad ;
   }
   return res;
   //unsigned char res = IO[0];
   /*printf("VALOR IO: %d \n", res);
	if (!((res >> 4) & 0b00000001)) {
		unsigned char bottomJoyPad = keys >> 4;
		bottomJoyPad |= 0xF0;
		res &= bottomJoyPad;

	}
	else {
		unsigned char topJoyPad = keys & 0xF;
		topJoyPad |= 0xF0;
		res &= topJoyPad;
	}*/
	return res;
}