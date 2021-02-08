#include <stdio.h>

#define FLAGS_ZERO (1 << 7)
#define FLAGS_NEGATIVE (1 << 6)
#define FLAGS_HALFCARRY (1 << 5)
#define FLAGS_CARRY (1 << 4)

#define FLAGS_ISZERO (registers.F & FLAGS_ZERO)
#define FLAGS_ISNEGATIVE (registers.F & FLAGS_NEGATIVE)
#define FLAGS_ISCARRY (registers.F & FLAGS_CARRY)
#define FLAGS_ISHALFCARRY (registers.F & FLAGS_HALFCARRY)

#define FLAGS_ISSET(x) (registers.F & (x))
#define FLAGS_SET(x) (registers.F |= (x))
#define FLAGS_CLEAR(x) (registers.F &= ~(x))

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

struct registros{
    unsigned char A;
    unsigned char F;
    unsigned char B;
    unsigned char C;
    unsigned char D;
    unsigned char E;
    unsigned char H;
    unsigned char L;
	unsigned short HL;
	unsigned short BC;
	unsigned short DE;
	unsigned short AF;
    unsigned short SP;
    unsigned short PC;
    unsigned char flags;
}registers;

struct registros2{
    unsigned char A;
    unsigned char F;
    unsigned char B;
    unsigned char C;
    unsigned char D;
    unsigned char E;
    unsigned char H;
    unsigned char L;
	unsigned short HL;
	unsigned short BC;
	unsigned short DE;
	unsigned short AF;
    unsigned short SP;
    unsigned short PC;
    unsigned char flags;
}regist;

static unsigned char rlc(unsigned char value) {
	int carry = (value & 0x80) >> 7;
	
	if(value & 0x80) FLAGS_SET(FLAGS_CARRY);
	else FLAGS_CLEAR(FLAGS_CARRY);
	
	value <<= 1;
	value += carry;
	
	if(value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	
	FLAGS_CLEAR(FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	return value;
}

static unsigned char rlc2(unsigned char registro){
    unsigned char u = registro >> 7;
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro= registro << 1;
	//como es una rotacion, se le mete al final lo que "salio"
	registro += u;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
    if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }
	

    return registro;
}

static unsigned char rrc(unsigned char value) {
	int carry = value & 0x01;
	
	value >>= 1;
	
	if(carry) {
		FLAGS_SET(FLAGS_CARRY);
		value |= 0x80;
	}
	else FLAGS_CLEAR(FLAGS_CARRY);
	
	if(value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	
	FLAGS_CLEAR(FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	return value;
}

static unsigned char rrc2(unsigned char registro){
	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = registro & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro= registro >> 1;
	//como es una rotacion, se le mete por el otro lado lo que salio
	registro += u << 7;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
}

static unsigned char rl(unsigned char value) {
	int carry = FLAGS_ISSET(FLAGS_CARRY) ? 1 : 0;
	
	if(value & 0x80) FLAGS_SET(FLAGS_CARRY);
	else FLAGS_CLEAR(FLAGS_CARRY);
	
	value <<= 1;
	value += carry;
	
	if(value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	
	FLAGS_CLEAR(FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	return value;
}


static unsigned char rl2(unsigned char registro){
	//cogemos el valor del bit de carry
	unsigned char bit=regist.F & 0x10;
	bit= bit >>4;
	bit= bit & 0x01;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	//vemos si el mas significativo de A es 1 o 0
	unsigned char u = registro >> 7;
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro = registro << 1;

	//como es una rotacion, se le mete al final lo que "salio"
	registro += bit;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;

}

static unsigned char rr(unsigned char value) {
	value >>= 1;
	if(FLAGS_ISCARRY) value |= 0x80;
	
	if(value & 0x01) FLAGS_SET(FLAGS_CARRY);
	else FLAGS_CLEAR(FLAGS_CARRY);
	
	if(value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	
	FLAGS_CLEAR(FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	return value;
}

static unsigned char rr2(unsigned char registro){
	//cogemos el valor del bit de carry
	unsigned char bit=regist.F & 0x10;
	bit= bit <<3;
	bit= bit & 0x80;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = registro & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	registro = registro >> 1;

	//como es una rotacion, se le mete al final lo que "salio"
	registro += bit;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;

}

static unsigned char sla(unsigned char value) {
	if(value & 0x80) FLAGS_SET(FLAGS_CARRY);
	else FLAGS_CLEAR(FLAGS_CARRY);
	
	value <<= 1;
	
	if(value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	
	FLAGS_CLEAR(FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	return value;
}

static unsigned char sla2(unsigned char registro){
    unsigned char u= registro >>7;
    if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}
    registro=registro<<1;

    regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
    
}

int main(){
    unsigned char A= 0x8F;
    unsigned char B= 0x00;

    unsigned char resultado1= (A & 0x80) >> 7;
    unsigned char resultado2= (B & 0x80) >> 7;
    unsigned char resultado3= A >> 7;
    unsigned char resultado4= B >> 7;

    unsigned char resultado5=sla(A);
    unsigned char resultado6=sla(B);
    unsigned char resultado7=sla2(A);
    unsigned char resultado8=sla2(B);

    //printf("Resultado 1:%u \n",resultado1);
    //printf("Resultado 2:%u \n",resultado2);
    //printf("Resultado 3:%u \n",resultado3);
    //printf("Resultado 4:%u \n",resultado4);


    //printf("Leading text1 \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado1));
    //printf("Leading text2 \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado2));
    //printf("Leading text3 \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado3));
    //printf("Leading text4 \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado4));
    printf("ORIGINAL A \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(A));
    printf("RESULTADO PAVO \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado5));
    printf("RESULTADO MIO \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado7));
    printf("ORIGINAL B \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(B));
    printf("RESULTADO PAVO \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado6));
    printf("RESULTADO MIO \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(resultado8));
    printf("RESULTADO F PAVO \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(registers.F));
    printf("RESULTADO F MIO \n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.F));


    
    return 0;
}