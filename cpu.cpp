#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "memoria.cpp"

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

using namespace std; 
	
struct instruction {
	int valid_instruction;
	int clock_cycle;
	int machine_cycle;
	void (*action)(void);
	
	//unsigned char ticks;

} extern const instructions[256];



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
    unsigned short SP;
    unsigned short PC;
    unsigned char flags;
}regist;

void reset(){
    regist.A = 0x01;
	regist.F = 0xb0;
	regist.B = 0x00;
	regist.C = 0x13;
	regist.D = 0x00;
	regist.E = 0xd8;
	regist.H = 0x01;
	regist.L = 0x4d;
	regist.SP = 0xfffe;
	regist.PC = 0x100;

	//HL
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;

	//DE
	regist.DE=regist.D;
	regist.DE=regist.DE<<8;
	regist.DE=regist.DE|regist.E;

	//BC
	regist.BC=regist.B;
	regist.BC=regist.BC<<8;
	regist.BC=regist.BC|regist.C;

}

void reconstruirHL(){
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
}

void deconstruirHL(){
	regist.H=(unsigned char) ((regist.HL >>8) & 0xFF);
	regist.L=(unsigned char) (regist.HL & 0xFF);
}

void reconstruirDE(){
	regist.DE=regist.D;
	regist.DE=regist.DE<<8;
	regist.DE=regist.DE|regist.E;
}

void deconstruirDE(){
	regist.D=(unsigned char) ((regist.DE >>8) & 0xFF);
	regist.E=(unsigned char) (regist.DE & 0xFF);
}

void reconstruirBC(){
	regist.BC=regist.B;
	regist.BC=regist.BC<<8;
	regist.BC=regist.BC|regist.C;
}

void deconstruirBC(){
	regist.B=(unsigned char) ((regist.BC >>8) & 0xFF);
	regist.C=(unsigned char) (regist.BC & 0xFF);
}

int machine_cycle=0;
int clock_cycle=0;

//funcion para indicar que ha habido acarreo
static void acarreo(){
	//activar flag con OR
	regist.F= regist.F | 0x10;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0xEF;

}

//HALF CARRY
static void half(){
		//activar flag con OR
	regist.F= regist.F | 0x20;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0xDF;
}

//SUBSTRACT N
static void SUBSTRACT(){
	//activar flag con OR
	regist.F= regist.F | 0x40;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0xBF;

}

//ZERO
static void zero(){
	//activar flag con OR
	regist.F= regist.F | 0x80;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0x7F;
}
//incrementar
static void inc(unsigned char *A) {
	unsigned char t=*A;
	printf("\n Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(t));
	if((*A & (unsigned char )0x0F) == 0x0F){ //Flag half carry
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	
	
	*A=*A + 0x01;
	t=*A;

	printf("\n Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(t));
	
	if(*A==0){ //Flag zero
		regist.F= regist.F | 0x80;
	}else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F & 0xBF; //Flag N
}

//incrementar de lo que coges de memoria
static unsigned char inc2(unsigned char A) {
	if((A & (unsigned char )0x0F) == 0x0F){ //Flag half carry
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	
	
	A=A + 0x01;
	
	if(A==0){ //Flag zero
		regist.F= regist.F | 0x80;
	}else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F & 0xBF; //Flag N

	return A;
}

//decrementar
static void dec(unsigned char *A) {
	if(*A & (unsigned char )0x0f){//flag half carry
		regist.F= regist.F & 0xDF;
	} 
	else{
		regist.F= regist.F | 0x20;
	}
	
	*A=*A - 0x01;
	
	if(*A==0){ //flag zero
		regist.F= regist.F | 0x80;
	} 
	else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F | 0x40; //flag N
	

}

//decrementar lo que coges de memoria
static unsigned char dec2(unsigned char A) {
	if(A & (unsigned char )0x0f){//flag half carry
		regist.F= regist.F & 0xDF;
	} 
	else{
		regist.F= regist.F | 0x20;
	}
	
	A=A - 0x01;
	
	if(A==0){ //flag zero
		regist.F= regist.F | 0x80;
	} 
	else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F | 0x40; //flag N
	
	return A;
}

//funcion normalita de add suma
static void suma(unsigned char *A, unsigned char B){
	char16_t carry= *A + B;
    char16_t temp2= *A + B;
	cout<< "\nVARIABLE CARRY MIENTRAS SUMA NORMAL";
	unsigned char t=(unsigned char)(temp2 & 0xFF);
	printf("\n Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(t));
	unsigned char half1=*A & 0x0F;
	unsigned char half2=B & 0x0F;
	unsigned char half3=half1 + half2;
    carry= carry >> 8;
	t=(unsigned char)(carry & 0xFF);
	cout<< "\n EL  CARRY DESPLAZADO"<< carry;
	printf("\n Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(t));

    if(carry > 0x01){
        regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	*A=(unsigned char)(temp2 & 0xFF);

	if(*A==0x00){ 
		regist.F= regist.F | 0x80;//flag ZERO
	}
	else{
		regist.F= regist.F & 0x7F;//desactivar ZERO		
	}
	if((half3>>4) >=0x01){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	regist.F= regist.F & 0xBF;

}

//funcion normalita de add suma, ahora con acarreo
static void sumaC(unsigned char *A, unsigned char B){
	unsigned char bit=regist.F & 0x10;
	bit= bit >>4;
	bit= bit & 0x01;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	unsigned char B2= B +bit;
	unsigned short carry= *A + B2;
	unsigned char normal= *A + B2;
	unsigned short segundocarry= *A + B2;
	
	cout<<"RATATATATATATATATATATATA";
	printf("\n Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(bit));
	unsigned char half1=*A & 0x0F;
	unsigned char half2=B2 & 0x0F;
	unsigned char half3=half1 + half2;//PUEDE HABER PROBLEMAS AQUI AL NO SUMAR EL BIT DE ACARREO
	
	//segundocarry= segundocarry + bit; //puede sumar 0 o 1 PUEDO HABERME EQUIVOCADO AL COPIAR Y PEGAR EL NOOMBRE SEGUNDO CARRY
	 carry= carry >> 8;
    if(carry > 0x01){
        regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	*A=(unsigned char)(segundocarry & 0xFF);

	if(*A==0x00){ 
		regist.F= regist.F | 0x80;//flag ZERO
	}
	else{
		regist.F= regist.F & 0x7F;//desactivar ZERO		
	}
	if((half3>>4) >=0x01){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	regist.F= regist.F & 0xBF;	

}

//hora de la funcion de restar normal, sin trampas
static void resta(unsigned char *A, unsigned char B){
	unsigned char temp2= *A - B;
	unsigned char half1= *A & 0x0F;
	unsigned char half2= B & 0x0F;

    if(B > *A){
        regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	*A=temp2;

	if(*A==0x00){ 
		regist.F= regist.F | 0x80;//flag ZERO
	}
	else{
		regist.F= regist.F & 0x7F;//desactivar ZERO		
	}
	if(half2 > half1){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	regist.F= regist.F | 0x40;

}


//RESTA RESC wololo
//hora de la funcion de restar normal, sin trampas
static void restaC(unsigned char *A, unsigned char B){
	unsigned char bit=regist.F & 0x10;
	bit= bit >>4;
	bit= bit & 0x01;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa
	
	unsigned char B2= B +bit;

    unsigned char temp2= *A - B2;
	unsigned char half1= *A & 0x0F;
	unsigned char half2= B2 & 0x0F;


    if(B2 > *A){
        regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	*A=temp2;

	if(*A==0x00){ 
		regist.F= regist.F | 0x80;//flag ZERO
	}
	else{
		regist.F= regist.F & 0x7F;//desactivar ZERO		
	}
	if(half2 > half1){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	regist.F= regist.F | 0x40;

}

//instruccion and
static void ando(unsigned char *A){
	regist.A= regist.A & *A;

	if(regist.A==0){//flag zero
		regist.F= regist.F | 0x80;
	} 
	else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F & 0xBF;//pone el flag de restar a 0;
	regist.F= regist.F & 0xEF;// flag carry
	regist.F= regist.F | 0x20;//activa el half
}

//instruccion or
static void oro(unsigned char *A){
	regist.A= regist.A | *A;

	if(regist.A==0){
		regist.F= regist.F | 0x80;
	}
	else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F & 0xBF;//pone el flag de restar a 0;
	regist.F= regist.F & 0xEF;// flag carry
	regist.F= regist.F & 0xDF;//activa el half
}


//La XOR
static void xoro(unsigned char *A){
	regist.A= regist.A ^ *A;

	if(regist.A==0){
		regist.F= regist.F | 0x80;
	}
	else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F & 0xBF;//pone el flag de restar a 0;
	regist.F= regist.F & 0xEF;// flag carry
	regist.F= regist.F & 0xDF;//activa el half
}

//el CP, altera los flags
static void cp(unsigned char A){
	if(regist.A==A){
		regist.F= regist.F | 0x80;
	}else{
		regist.F= regist.F & 0x7F;
	}

	if(regist.A<A){
		regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;
	}

	if((A & 0x0F) > (regist.A & 0x0F)){
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}

}

//NOP 0x00
void nop(){
	clock_cycle+=4;
	machine_cycle++;
}

// 0x03
void inc_bc() { 
	reconstruirBC();
	regist.BC=regist.BC + 0x01;
	deconstruirBC(); 
} //en estas no se comprueban flags

// 0x04
void inc_b(void) { 
	inc(&regist.B);
	reconstruirBC();
}

// 0x05
void dec_b() { 
	dec(&regist.B);
	reconstruirBC();
}

// 0x0b
void dec_bc() { 
	reconstruirBC();
	regist.BC=regist.BC - 0x01;
	deconstruirBC(); 
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x0c
void inc_c() { 
	inc(&regist.C); 
	reconstruirBC();	
}

// 0x0d
void dec_c() { 
	dec(&regist.C);
	reconstruirBC();

}


// 0x13
void inc_de() { 
	reconstruirDE();
	regist.DE=regist.DE + 0x01; 
	deconstruirDE();
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x14
void inc_d() {
	inc(&regist.D);
	reconstruirDE();
}

// 0x15
void dec_d() {
	dec(&regist.D);
	reconstruirDE();	
}


// 0x1b
void dec_de() { 
	reconstruirDE();
	regist.DE=regist.DE - 0x01;
	deconstruirDE();
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x1c
void inc_e() {
	inc(&regist.E); 
	reconstruirDE();
}

// 0x1d
void dec_e() {
	dec(&regist.E); 
	reconstruirHL();
}


// 0x23
void inc_hl() {  
	reconstruirHL();
	regist.HL=regist.HL + 0x01;
	deconstruirHL();
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x24
void inc_h() { 
	inc(&regist.H); 
	reconstruirHL();

}

// 0x25
void dec_h() { 
	dec(&regist.H);
	reconstruirHL();
}


// 0x2b
void dec_hl() { 
	reconstruirHL();
	regist.HL=regist.HL - 0x01;
	deconstruirHL(); 
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x2c
void inc_l() { 
	inc(&regist.L); 
	reconstruirHL();
}

// 0x2d
void dec_l() { 
	dec(&regist.L); 
	reconstruirHL();
}


// 0x33
void inc_sp() { regist.SP++; }

// 0x34
void inc_hlm() {
	char16_t patata=regist.HL;
	unsigned char temp=inc2(loadMEMB(regist.HL));

	writeMEMB(patata, temp);
}

// 0x35
void dec_hlm() {
	char16_t patata=regist.HL;
	unsigned char temp=dec2(loadMEMB(regist.HL));

	writeMEMB(patata, temp);
}


// 0x3b
void dec_sp() { regist.SP=regist.SP - 0x01; }

// 0x3c
void inc_a() { inc(&regist.A); }

// 0x3d
void dec_a() { dec(&regist.A); }


//LD B, C  0x40, copia B a B
void ld_b_b() { 
	regist.B = regist.B;
	
}

//LD B, C  0x41, copia C a B
void ld_b_c() { regist.B = regist.C;
}

//LD B, D  0x42, copia D a B
void ld_b_d() { regist.B = regist.D;
}

//LD B, E  0x43, copia E a B
void ld_b_e() { regist.B = regist.E;}

//LD B, H  0x44, copia H a B
void ld_b_h() { regist.B = regist.H;}

//LD B, L  0x45, copia L a B
void ld_b_l() { regist.B = regist.L;}

//LD B, HL  0x46, carga HL a B
void ld_b_hl() { 
	
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.B = loadMEMB(regist.HL);
	}

//LD B, A  0x47, copia A a B
void ld_b_a() { regist.B = regist.A;}

//LD C, B 0x48, copia B a C
void ld_c_b() {regist.C = regist.B;}

//LD C, C 0x49, copia C a C
void ld_c_c() {regist.C = regist.C;}

//LD C, D 0x4a, copia D a C
void ld_c_d() {regist.C = regist.D;}

//LD C, e 0x4b, copia E a C
void ld_c_e() {regist.C = regist.E;}

//LD C, B 0x4c, copia H a C
void ld_c_h() {regist.C = regist.H;}

//LD C, B 0x4d, copia L a C
void ld_c_l() {regist.C = regist.L;}

//LD C, HL  0x4e, carga HL a C
void ld_c_hl() { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.C = loadMEMB(regist.HL);
	}

//LD C, A  0x4f, copia A a C
void ld_c_a() {regist.C = regist.A;}

//LD D, B 0x50, copia B a D
void ld_d_b() {regist.D = regist.B;}

//LD D, C 0x51, copia C a D
void ld_d_c() {regist.D = regist.C;}

//LD D, D 0x52, copia D a D
void ld_d_d() {regist.D = regist.D;}

//LD D, e 0x53, copia E a D
void ld_d_e() {regist.D = regist.E;}

//LD D, B 0x54, copia H a D
void ld_d_h() {regist.D = regist.H;}

//LD D, B 0x55, copia L a D
void ld_d_l() {regist.D = regist.L;}

//LD D, HL  0x56, carga HL a D
void ld_d_hl() { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.D = loadMEMB(regist.HL);
	}

//LD E, A  0x57, copia A a E
void ld_d_a() {regist.D = regist.A;}

//LD E, B 0x58, copia B a E
void ld_e_b() {regist.E = regist.B;}

//LD E, C 0x59, copia C a E
void ld_e_c() {regist.E = regist.C;}

//LD E, D 0x5a, copia D a E
void ld_e_d() {regist.E = regist.D;}

//LD E, e 0x5b, copia E a E
void ld_e_e() {regist.E = regist.E;}

//LD E, B 0x5c, copia H a E
void ld_e_h() {regist.E = regist.H;}

//LD E, B 0x5d, copia L a E
void ld_e_l() {regist.E = regist.L;}

//LD E, HL  0x5e, carga HL a E
void ld_e_hl() { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.E = loadMEMB(regist.HL);
	}

//LD E, A  0x5f, copia A a E
void ld_e_a() {regist.E = regist.A;}

//LD H, B 0x60, copia B a H
void ld_h_b() {regist.H = regist.B;}

//LD H, C 0x61, copia C a H
void ld_h_c() {regist.H = regist.C;}

//LD H, D 0x62, copia D a H
void ld_h_d() {regist.H = regist.D;}

//LD H, e 0x63, copia E a H
void ld_h_e() {regist.H = regist.E;}

//LD H, B 0x64, copia H a H
void ld_h_h() {regist.H = regist.H;}

//LD H, B 0x65, copia L a H
void ld_h_l() {regist.H = regist.L;}

//LD H, HL  0x66, carga HL a H
void ld_h_hl() { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.H = loadMEMB(regist.HL);
	}

//LD H, A  0x67, copia A a H
void ld_h_a() {regist.H = regist.A;}

//LD L, B 0x68, copia B a L
void ld_l_b() {regist.L = regist.B;}

//LD L, C 0x69, copia C a L
void ld_l_c() {regist.L = regist.C;}

//LD L, D 0x6a, copia D a L
void ld_l_d() {regist.L = regist.D;}

//LD L, e 0x6b, copia E a L
void ld_l_e() {regist.L = regist.E;}

//LD L, B 0x6c, copia H a L
void ld_l_h() {regist.L = regist.H;}

//LD L, B 0x6d, copia L a L
void ld_l_l() {regist.L = regist.L;}

//LD L, HL  0x6e, carga HL a L
void ld_l_hl() { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.L = loadMEMB(regist.HL);
	}

//LD L, A  0x6f, copia A a L
void ld_l_a() {regist.L = regist.A;}

//LD (HL), B  0x70, guarda en mem B en la direccion de HL
void ld_hl_b() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.B);
}

//LD (HL), C  0x71, guarda en mem C en la direccion de HL
void ld_hl_c() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.C);
}

//LD (HL), D  0x72, guarda en mem D en la direccion de HL
void ld_hl_d() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.D);
}

//LD (HL), E  0x73, guarda en mem E en la direccion de HL
void ld_hl_e() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.E);
}

//LD (HL), H  0x74, guarda en mem H en la direccion de HL
void ld_hl_h() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.H);
}

//LD (HL), L  0x75, guarda en mem L en la direccion de HL
void ld_hl_l() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.L);
}

int interrrupt_enable=0;

void keyboardInterrupt(int signal){
	if(signal==SIGINT){
		interrrupt_enable=1;
		printf("probar señal ¿TECLADO?");

	}

}

//HALT 0x76
void halt(){
	clock_cycle+=4;
	machine_cycle++;
	while(!interrrupt_enable){
		pause();

}

	regist.PC++;
	
}

//LD (HL), A  0x77, guarda en mem A en la direccion de HL
void ld_hl_a() {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.A);
}

//LD A, B 0x78, copia B a A
void ld_a_b() {regist.A = regist.B;}

//LD A, C 0x79, copia C a A
void ld_a_c() {regist.A = regist.C;}

//LD A, D 0x7a, copia D a A
void ld_a_d() {regist.A = regist.D;}

//LD A, E 0x7b, copia E a A
void ld_a_e() {regist.A = regist.E;}

//LD A, B 0x7c, copia H a A
void ld_a_h() {regist.A = regist.H;}

//LD A, B 0x7d, copia L a A
void ld_a_l() {regist.A = regist.L;}

//LD A, HL  0x7e, carga HL a A
void ld_a_hl() { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.A = loadMEMB(regist.HL);
	}

//LD A, A  0x7f, copia A a A
void ld_a_a() {regist.A = regist.A;}

//ADD A, B 0x80, Suma A y B y lo guarda en A
void add_a_b(){
	suma(&regist.A, regist.B);

}

//ADD A, C 0x81, Suma A y C y lo guarda en A
void add_a_c(){
	suma(&regist.A, regist.C);


}

//ADD A, D 0x82, Suma A y D y lo guarda en A
void add_a_d(){
	suma(&regist.A, regist.D);

}

//ADD A, E 0x83, Suma A y E y lo guarda en A
void add_a_e(){
	suma(&regist.A, regist.E);

}

//ADD A, H 0x84, Suma A y H y lo guarda en A
void add_a_h(){
	suma(&regist.A, regist.H);

}

//ADD A, L 0x85, Suma A y L y lo guarda en A
void add_a_l(){
	suma(&regist.A, regist.L);

}

//ADD A, HL 0x86, Suma A y (HL) y lo guarda en A
void add_a_hl(){
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	suma(&regist.A, temp);
}

//ADD A, A 0x87, Suma A y A y lo guarda en A
void add_a_a(){
	suma(&regist.A, regist.A);

}

//ADC A, B, 0x88 Suma A y B con acarreo, se guarda en A
void adc_a_b(){
	sumaC(&regist.A, regist.B);

}

//ADC A, C, 0x89 Suma A y C con acarreo, se guarda en A
void adc_a_c(){
	sumaC(&regist.A, regist.C);

}

//ADC A, D, 0x8a Suma A y D con acarreo, se guarda en A
void adc_a_d(){
	sumaC(&regist.A, regist.D);
;
}

//ADC A, E, 0x8b Suma A y E con acarreo, se guarda en A
void adc_a_e(){
	sumaC(&regist.A, regist.E);

}

//ADC A, H, 0x8c Suma A y H con acarreo, se guarda en A
void adc_a_h(){
	sumaC(&regist.A, regist.H);

}

//ADC A, L, 0x8d Suma A y L con acarreo, se guarda en A
void adc_a_l(){
	sumaC(&regist.A, regist.L);

}

//ADC A, (HL), 0x8e Suma A y (HL) con acarreo, se guarda en A
void adc_a_hl(){
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	sumaC(&regist.A, temp);
}

//ADC A, A, 0x8f Suma A y A con acarreo, se guarda en A
void adc_a_a(){
	sumaC(&regist.A, regist.A);

}

//SUB A, B 0x90, resta A y B y lo guarda en A
void sub_a_b(){
	resta(&regist.A, regist.B);

}

//SUB A, C 0x91, resta A y C y lo guarda en A
void sub_a_c(){
	resta(&regist.A, regist.C);

}

//SUB A, D 0x92, resta A y D y lo guarda en A
void sub_a_d(){
	resta(&regist.A, regist.D);

}

//SUB A, E 0x93, resta A y E y lo guarda en A
void sub_a_e(){
	resta(&regist.A, regist.E);

}

//SUB A, H 0x94, resta A y H y lo guarda en A
void sub_a_h(){
	resta(&regist.A, regist.H);

}

//SUB A, L 0x95, resta A y L y lo guarda en A
void sub_a_l(void){
	resta(&regist.A, regist.L);

}

//SUB A, HL 0x96, resta A y (HL) y lo guarda en A
void sub_a_hl(void){
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	resta(&regist.A, temp);
}

//SUB A, A 0x97, resta A y A y lo guarda en A
void sub_a_a(void){
	resta(&regist.A, regist.A);

}



// 0x98
void sbc_a_b(void) { restaC(&regist.A, regist.B); }

// 0x99
void sbc_a_c(void) { restaC(&regist.A, regist.C); }

// 0x9a
void sbc_a_d(void) { restaC(&regist.A, regist.D); }

// 0x9b
void sbc_a_e(void) { restaC(&regist.A, regist.E); }

// 0x9c
void sbc_a_h(void) { restaC(&regist.A, regist.H); }

// 0x9d
void sbc_a_l(void) { restaC(&regist.A, regist.L); }

// 0x9e
void sbc_a_hl(void) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	restaC(&regist.A, temp);
}

// 0x9f
void sbc_a_a(void) { restaC(&regist.A, regist.A); }

// 0xa0
void and_b(void) { ando(&regist.B); }

// 0xa1
void and_c(void) { ando(&regist.C); }

// 0xa2
void and_d(void) { ando(&regist.D); }

// 0xa3
void and_e(void) { ando(&regist.E); }

// 0xa4
void and_h(void) { ando(&regist.H); }

// 0xa5
void and_l(void) { ando(&regist.L); }

// 0xa6
void and_hlp(void) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L; 
	unsigned char temp= loadMEMB(regist.HL);
	ando(&temp);
}

// 0xa7
void and_a(void) { ando(&regist.A); }

// 0xa8
void xor_b(void) { xoro(&regist.B); }

// 0xa9
void xor_c(void) { xoro(&regist.C); }

// 0xaa
void xor_d(void) { xoro(&regist.D); }

// 0xab
void xor_e(void) { xoro(&regist.E); }

// 0xac
void xor_h(void) { xoro(&regist.H); }

// 0xad
void xor_l(void) { xoro(&regist.L); }

// 0xae
void xor_hlp(void) { 
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	xoro(&temp);
}

// 0xaf
void xor_a(void) { xoro(&regist.A); }

// 0xb0
void or_b(void) { oro(&regist.B); }

// 0xb1
void or_c(void) { oro(&regist.C); }

// 0xb2
void or_d(void) { oro(&regist.D); }

// 0xb3
void or_e(void) { oro(&regist.E); }

// 0xb4
void or_h(void) { oro(&regist.H); }

// 0xb5
void or_l(void) { oro(&regist.L); }

// 0xb6
void or_hlp(void) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L; 
	unsigned char temp= loadMEMB(regist.HL);
	oro(&temp);
}

// 0xb7
void or_a(void) { oro(&regist.A); }

// 0xb8
void cp_b(void) { cp(regist.B); }

// 0xb9
void cp_c(void) { cp(regist.C); }

// 0xba
void cp_d(void) { cp(regist.D); }

// 0xbb
void cp_e(void) { cp(regist.E); }

// 0xbc
void cp_h(void) { cp(regist.H); }

// 0xbd
void cp_l(void) { cp(regist.L); }

// 0xbe
void cp_hlp(void) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L; 
	unsigned char temp= loadMEMB(regist.HL);
	cp(temp);
}

// 0xbf
void cp_a(void) { cp(regist.A); }


const struct instruction instructions[256]={
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x00
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x01
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x02
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_bc }, //0x03
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_b }, //0x04
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_b }, //0x05
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x06
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x07
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x08
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x09
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x0a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_bc }, //0x0b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_c }, //0x0c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_c }, //0x0d
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x0c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x0d
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x0e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x0f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x10
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x11
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x12
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_de }, //0x13
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_d }, //0x14
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_d }, //0x15
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x16
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x17
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x18
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x19
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x1a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_de }, //0x1b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_e }, //0x1c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_e }, //0x1d
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x1e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x1f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x20
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x21
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x22
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_hl }, //0x23
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_h }, //0x24
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_h }, //0x25
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x26
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x27
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x28
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x29
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x2a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_hl }, //0x2b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_l }, //0x2c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_l }, //0x2d
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x2e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x2f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x30
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x31
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x32
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_sp }, //0x33
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_hlm }, //0x34
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_hlm }, //0x35
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x36
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x37
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x38
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x39
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:nop }, //0x3a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_sp }, //0x3b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:inc_a }, //0x3c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:dec_a }, //0x3d
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_b }, //0x40
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_c }, //0x41
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_d }, //0x42
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_e }, //0x43
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_h }, //0x44
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_l }, //0x45
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_b_hl }, //0x46
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_b_a }, //0x47
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_b }, //0x48
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_c }, //0x49
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_d }, //0x4a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_e }, //0x4b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_h }, //0x4c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_l }, //0x4d
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_c_hl }, //0x4e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_c_a }, //0x4f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_b }, //0x50
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_c }, //0x51
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_d }, //0x52
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_e }, //0x53
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_h }, //0x54
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_l }, //0x55
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_d_hl }, //0x56
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_d_a }, //0x57
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_b }, //0x58
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_c }, //0x59
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_d }, //0x5a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_e }, //0x5b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_h }, //0x5c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_l }, //0x5d
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_e_hl }, //0x5e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_e_a }, //0x5f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_b }, //0x60
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_c }, //0x61
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_d }, //0x62
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_e }, //0x63
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_h }, //0x64
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_l }, //0x65
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_h_hl }, //0x66
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_h_a }, //0x67
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_b }, //0x68
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_c }, //0x69
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_d }, //0x6a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_e }, //0x6b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_h }, //0x6c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_l }, //0x6d
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_l_hl }, //0x6e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_l_a }, //0x6f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_b }, //0x70
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_c }, //0x71
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_d }, //0x72
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_e }, //0x73
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_h }, //0x74
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_l }, //0x75
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:halt }, //0x76
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_hl_a }, //0x77
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_b }, //0x78
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_c }, //0x79
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_d }, //0x7a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_e }, //0x7b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_h }, //0x7c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_l }, //0x7d
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:ld_a_hl }, //0x7e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:ld_a_a }, //0x7f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_b }, //0x80
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_c }, //0x81
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_d }, //0x82
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_e }, //0x83
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_h }, //0x84
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_l }, //0x85
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:add_a_hl }, //0x86
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:add_a_a }, //0x87
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_b }, //0x88
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_c }, //0x89
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_d }, //0x8a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_e }, //0x8b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_h }, //0x8c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_l }, //0x8d
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:adc_a_hl }, //0x8e
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:adc_a_a }, //0x8f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sub_a_b }, //0x90
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sub_a_c }, //0x91
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sub_a_d }, //0x92
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sub_a_e }, //0x93
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sub_a_h }, //0x94
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sub_a_l }, //0x95
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sub_a_hl }, //0x96
	{ 1, 4, 1,sub_a_a }, //0x97
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sbc_a_b }, //0x98
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sbc_a_c }, //0x99
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sbc_a_d }, //0x9a
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sbc_a_e }, //0x9b
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sbc_a_h }, //0x9c
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:sbc_a_l }, //0x9d
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sbc_a_hl }, //0x9e
	{ 1, 4, 1,sbc_a_a }, //0x9f
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:and_b }, //0xa0
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:and_c }, //0xa1
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:and_d }, //0xa2
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:and_e }, //0xa3
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:and_h }, //0xa4
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:and_l }, //0xa5
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:and_hlp }, //0xa6
	{ 1, 4, 1,and_a }, //0xa7
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:xor_b }, //0xa8
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:xor_c }, //0xa9
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:xor_d }, //0xaa
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:xor_e }, //0xab
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:xor_h }, //0xac
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:xor_l }, //0xad
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:xor_hlp }, //0xae
	{ 1, 4, 1,xor_a }, //0xaf
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:or_b }, //0xb0
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:or_c }, //0xb1
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:or_d }, //0xb2
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:or_e }, //0xb3
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:or_h }, //0xb4
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:or_l }, //0xb5
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:or_hlp }, //0xb6
	{ 1, 4, 1,or_a }, //0xb7
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:cp_b }, //0xb8
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:cp_c }, //0xb9
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:cp_d }, //0xba
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:cp_e }, //0xbb
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:cp_h }, //0xbc
	{ valid_instruction:true, clock_cycle:4, machine_cycle:1, action:cp_l }, //0xbd
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:cp_hlp }, //0xbe
	{ 1, 4, 1,cp_a }, //0xbf


};

int main(int argc, char **argv){

	char mem[2500];
    // leer file
    /*long addr, value ;
	FILE *fd = fopen("file.rom","r") ;
	if (fd == NULL) {
    	perror("horror: ") ;
		return -1 ;
    }
	int pc=0;
	while (!feof(fd))
	{
      //fscanf(fd, "%d: %d", &addr, &value);
	  fscanf(fd, "%d", &value);
	   mem[pc] = value ;
	   pc++;
	   
    }*/

	int i=0;
	reset();
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.F));
	mem[0]=0x00;
	mem[1]=0x3C;
	//incrementar B
	//instructions[0x04].action();
	//incrementar C
	//instructions[0x0c].action();
	//Sumar A + B
	//instructions[0x88].action();
	//Sumar A + C
	instructions[0x81].action();
	cout<< "\nRegistro B: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.B));
	cout<< "\nRegistro C: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.C));
	
	cout<< "\nRegistro A: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.A));
	cout<< "\nRegistro F: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.F));
	cout<< "\nRegistro D " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.D));
	cout<< "\nRegistro E: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.E));
	cout<< "\nRegistro H: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.H));
	cout<< "\nRegistro L: " <<endl;
	printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.L));
	

	//printf(" Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(regist.B));
	/*cout<< "Registro A: " <<regist.A << "\n" << "Registro B: " <<regist.B <<"\n" << "Registro F: " << regist.F <<"\n" << "Registro C: " << regist.C <<"\n" << "Registro D: " << regist.D
		<<"\n" << "Registro E: " << regist.E  <<"\n" << "Registro H: " << regist.H  <<"\n" << "Registro L: " << regist.L  <<"\n" << "Registro HL: " << regist.HL  <<"\n" << "Registro SP: " << regist.SP
		<<"\n" << "Registro DE: " << regist.DE <<"\n" << "Registro PC: " << regist.PC  <<"\n" << "Registro BC: " << regist.BC << "\n" << endl;   
	*/
    // ejecutar
	/*while(1){
		i=mem[pc];//Sera un array mem[]??¿?¿?¿?
		if (instructions[i].valid_instruction) {
		    instructions[i].action();//Se escribe asi la sentencia en una funcion lambda¿?¿
		}
		cout<< "Registro A: " <<regist.A << "\n" << "Registro B: " <<regist.B <<"\n" << "Registro F: " << regist.F <<"\n" << "Registro C: " << regist.C <<"\n" << "Registro D: " << regist.D
		<<"\n" << "Registro E: " << regist.E  <<"\n" << "Registro H: " << regist.H  <<"\n" << "Registro L: " << regist.L  <<"\n" << "Registro HL: " << regist.HL  <<"\n" << "Registro SP: " << regist.SP
		<<"\n" << "Registro DE: " << regist.DE <<"\n" << "Registro PC: " << regist.PC  <<"\n" << "Registro BC: " << regist.BC << "\n" << endl;   
		cout<< "Siguiente instruccion: "<< mem[pc] <<endl;
		machine_cycle+=instructions[i].machine_cycle;
		clock_cycle+=instructions[i].clock_cycle;
		pc++;
	}*/

    return 0;

}


