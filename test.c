#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

unsigned char f=0x00;

#define FLAGS_ZERO (1 << 7)
#define FLAGS_NEGATIVE (1 << 6)
#define FLAGS_HALFCARRY (1 << 5)
#define FLAGS_CARRY (1 << 4)

#define FLAGS_ISZERO (f & FLAGS_ZERO)
#define FLAGS_ISNEGATIVE (f & FLAGS_NEGATIVE)
#define FLAGS_ISCARRY (f & FLAGS_CARRY)
#define FLAGS_ISHALFCARRY (f & FLAGS_HALFCARRY)

#define FLAGS_ISSET(x) (f & (x))
#define FLAGS_SET(x) (f |= (x))
#define FLAGS_CLEAR(x) (f &= ~(x))

unsigned char a= 0x8F;

void rlca(void) {
	unsigned char carry = ( a & 0x80) >> 7;
	if(carry != 0) FLAGS_SET(FLAGS_CARRY);
	else FLAGS_CLEAR(FLAGS_CARRY);
	
	a = a << 1;
	a += carry;
	
	FLAGS_CLEAR(FLAGS_NEGATIVE | FLAGS_ZERO | FLAGS_HALFCARRY);
}

int main(){
    unsigned char u = 0xFF & 0x01;
    u = u<<7;
    
    printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(u));
    rlca();
    printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(a));
printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(f));
    
    return 0;
}
