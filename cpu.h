#pragma once

struct instruction {
	
	int clock_cycle;
	int machine_cycle;
	void (*action)(unsigned int);
	int action_bit_number;
	unsigned int action_parameter;

};
extern struct instruction instructions[256];

void reconstruirHL () ;
void deconstruirHL () ;
void reconstruirDE () ;
void deconstruirDE () ;
void reconstruirBC () ;
void deconstruirBC () ;
static void zero ( ) ;
static void SUBSTRACT ( ) ;
static void half ( ) ;
static void acarreo ( ) ;


void nada (unsigned int) ;
//void inc_b (unsigned int) ;


void nop (unsigned int) ;
void ld_bc16(char16_t valor);
void ld_bca (unsigned int) ;
void inc_bc (unsigned int) ;
void inc_b (unsigned int) ;
void dec_b (unsigned int) ;
void ld_b8(unsigned char valor);
void rlca (unsigned int) ;
void LD_a16_sp(char16_t direccion);
void add_hl_bc (unsigned int) ;
void ld_a_bc (unsigned int) ;
void dec_bc (unsigned int) ;
void inc_c (unsigned int) ;
void dec_c (unsigned int) ;
void ld_c8(unsigned char valor);
void rrca (unsigned int) ;
void stop (unsigned int) ;
void ld_de16(char16_t valor);
void ld_dea (unsigned int) ;
void inc_de (unsigned int) ;
void inc_d (unsigned int) ;
void dec_d (unsigned int) ;
void ld_d8(unsigned char valor);
void rla (unsigned int) ;
void jr_r8(char valor);
void add_hl_de (unsigned int) ;
void ld_a_de (unsigned int) ;
void dec_de (unsigned int) ;
void inc_e (unsigned int) ;
void dec_e (unsigned int) ;
void ld_e8(unsigned char valor);
void rra (unsigned int) ;
void jr_nr8(char valor);
void ld_hl16(char16_t valor);
void ld_hla (unsigned int) ;
void inc_hl (unsigned int) ;
void inc_h (unsigned int) ;
void dec_h (unsigned int) ;
void ld_h8(unsigned char valor);
void DAA (unsigned int) ;
void jr_zr8(char valor);
void add_hl_hl (unsigned int) ;
void ld_a_hll (unsigned int) ;
void dec_hl (unsigned int) ;
void inc_l (unsigned int) ;
void dec_l (unsigned int) ;
void ld_l8(unsigned char valor);
void cpl (unsigned int) ;
void jr_ncr8(char valor);
void ld_sp16(char16_t valor);
void ld_hlma (unsigned int) ;
void inc_sp (unsigned int) ;
void inc_hlm (unsigned int) ;
void dec_hlm (unsigned int) ;
void ld_hlld8(unsigned char valor);
void scf (unsigned int) ;
void jr_cr8( char valor);
void add_hl_SP (unsigned int) ;
void ld_a_hlm (unsigned int) ;
void dec_sp (unsigned int) ;
void inc_a (unsigned int) ;
void dec_a (unsigned int) ;
void ld_a8(unsigned char valor);
void CCF (unsigned int) ;
void ld_b_b (unsigned int) ;
void ld_b_c (unsigned int) ;
void ld_b_d (unsigned int) ;
void ld_b_e (unsigned int) ;
void ld_b_h (unsigned int) ;
void ld_b_l (unsigned int) ;
void ld_b_hl (unsigned int) ;
void ld_b_a (unsigned int) ;
void ld_c_b (unsigned int) ;
void ld_c_c (unsigned int) ;
void ld_c_d (unsigned int) ;
void ld_c_e (unsigned int) ;
void ld_c_h (unsigned int) ;
void ld_c_l (unsigned int) ;
void ld_c_hl (unsigned int) ;
void ld_c_a (unsigned int) ;
void ld_d_b (unsigned int) ;
void ld_d_c (unsigned int) ;
void ld_d_d (unsigned int) ;
void ld_d_e (unsigned int) ;
void ld_d_h (unsigned int) ;
void ld_d_l (unsigned int) ;
void ld_d_hl (unsigned int) ;
void ld_d_a (unsigned int) ;
void ld_e_b (unsigned int) ;
void ld_e_c (unsigned int) ;
void ld_e_d (unsigned int) ;
void ld_e_e (unsigned int) ;
void ld_e_h (unsigned int) ;
void ld_e_l (unsigned int) ;
void ld_e_hl (unsigned int) ;
void ld_e_a (unsigned int) ;
void ld_h_b (unsigned int) ;
void ld_h_c (unsigned int) ;
void ld_h_d (unsigned int) ;
void ld_h_e (unsigned int) ;
void ld_h_h (unsigned int) ;
void ld_h_l (unsigned int) ;
void ld_h_hl (unsigned int) ;
void ld_h_a (unsigned int) ;
void ld_l_b (unsigned int) ;
void ld_l_c (unsigned int) ;
void ld_l_d (unsigned int) ;
void ld_l_e (unsigned int) ;
void ld_l_h (unsigned int) ;
void ld_l_l (unsigned int) ;
void ld_l_hl (unsigned int) ;
void ld_l_a (unsigned int) ;
void ld_hl_b (unsigned int) ;
void ld_hl_c (unsigned int) ;
void ld_hl_d (unsigned int) ;
void ld_hl_e (unsigned int) ;
void ld_hl_h (unsigned int) ;
void ld_hl_l (unsigned int) ;
void halt (unsigned int) ;
void ld_hl_a (unsigned int) ;
void ld_a_b (unsigned int) ;
void ld_a_c (unsigned int) ;
void ld_a_d (unsigned int) ;
void ld_a_e (unsigned int) ;
void ld_a_h (unsigned int) ;
void ld_a_l (unsigned int) ;
void ld_a_hl (unsigned int) ;
void ld_a_a (unsigned int) ;
void add_a_b (unsigned int) ;
void add_a_c (unsigned int) ;
void add_a_d (unsigned int) ;
void add_a_e (unsigned int) ;
void add_a_h (unsigned int) ;
void add_a_l (unsigned int) ;
void add_a_hl (unsigned int) ;
void add_a_a (unsigned int) ;
void adc_a_b (unsigned int) ;
void adc_a_c (unsigned int) ;
void adc_a_d (unsigned int) ;
void adc_a_e (unsigned int) ;
void adc_a_h (unsigned int) ;
void adc_a_l (unsigned int) ;
void adc_a_hl (unsigned int) ;
void adc_a_a (unsigned int) ;
void sub_a_b (unsigned int) ;
void sub_a_c (unsigned int) ;
void sub_a_d (unsigned int) ;
void sub_a_e (unsigned int) ;
void sub_a_h (unsigned int) ;
void sub_a_l (unsigned int) ;
void sub_a_hl (unsigned int) ;
void sub_a_a (unsigned int) ;
void sbc_a_b (unsigned int) ;
void sbc_a_c (unsigned int) ;
void sbc_a_d (unsigned int) ;
void sbc_a_e (unsigned int) ;
void sbc_a_h (unsigned int) ;
void sbc_a_l (unsigned int) ;
void sbc_a_hl (unsigned int) ;
void sbc_a_a (unsigned int) ;
void and_b (unsigned int) ;
void and_c (unsigned int) ;
void and_d (unsigned int) ;
void and_e (unsigned int) ;
void and_h (unsigned int) ;
void and_l (unsigned int) ;
void and_hlp (unsigned int) ;
void and_a (unsigned int) ;
void xor_b (unsigned int) ;
void xor_c (unsigned int) ;
void xor_d (unsigned int) ;
void xor_e (unsigned int) ;
void xor_h (unsigned int) ;
void xor_l (unsigned int) ;
void xor_hlp (unsigned int) ;
void xor_a (unsigned int) ;
void or_b (unsigned int) ;
void or_c (unsigned int) ;
void or_d (unsigned int) ;
void or_e (unsigned int) ;
void or_h (unsigned int) ;
void or_l (unsigned int) ;
void or_hlp (unsigned int) ;
void or_a (unsigned int) ;
void cp_b (unsigned int) ;
void cp_c (unsigned int) ;
void cp_d (unsigned int) ;
void cp_e (unsigned int) ;
void cp_h (unsigned int) ;
void cp_l (unsigned int) ;
void cp_hlp (unsigned int) ;
void cp_a (unsigned int) ;
void ret_nz (unsigned int) ;
void pop_bc (unsigned int) ;
void jp_nz_a16(unsigned short valor);
void jp_a16(unsigned short valor);
void call_nz_a16(unsigned short valor);
void push_bc (unsigned int) ;
void add_a_d8(unsigned char valor);
void rst_00h (unsigned int) ;
void ret_z (unsigned int) ;
void ret (unsigned int) ;
void jp_z_a16(unsigned short valor);
void call_z_a16(unsigned short valor);
void call_a16(unsigned short valor);
void adc_a_d8(unsigned char valor);
void RST_08H (unsigned int) ;
void ret_nc (unsigned int) ;
void pop_de (unsigned int) ;
void jp_nc_a16(unsigned short valor);
void call_nc_a16(unsigned short valor);
void push_de (unsigned int) ;
void sub_d8(unsigned char valor);
void rst_10h (unsigned int) ;
void ret_c (unsigned int) ;
void reti (unsigned int) ;
void jp_c_a16(unsigned short valor);
void call_c_a16(unsigned short valor);
void sbc_a_d8(unsigned char valor);
void rst_18h (unsigned int) ;
void ldh_a8_a(unsigned char valor);
void pop_hl (unsigned int) ;
void ld_ca (unsigned int) ;
void push_hl (unsigned int) ;
void and_d8(unsigned char valor);
void rst_20h (unsigned int) ;
void add_sp_r8(char valor);
void jp_hl (unsigned int) ;
void ld_a16_a(unsigned short valor);
void xor_d8(unsigned char valor);
void rst_28h (unsigned int) ;
void ldh_a_a8(unsigned char valor);
void pop_af (unsigned int) ;
void la_ac (unsigned int) ;
void di (unsigned int) ;
void push_af (unsigned int) ;
void or_d8(unsigned char valor);
void rst_30h (unsigned int) ;
void ld_hl_spr8(char valor);
void ld_sp_hl (unsigned int) ;
void ld_a_a16(unsigned short valor);
void ei (unsigned int) ;
void cp_d8(unsigned char valor);
void rst_38h (unsigned int) ;