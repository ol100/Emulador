#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include <string>
#include "registro.h"
#include "memoria.h"
#include "cpu.h"
#include "ExtendedCPU.h"


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
	
struct registros regist;
struct instruction instructions[256]={
	{   clock_cycle:4, machine_cycle:1, action:nop, action_bit_number:0, action_parameter:0}, //0x00
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ld_bc16, action_bit_number:16, action_parameter:2 }, //0x01 
	{   clock_cycle:8, machine_cycle:2, action:ld_bca, action_bit_number:0, action_parameter:0 }, //0x02
	{   clock_cycle:8, machine_cycle:2, action:inc_bc, action_bit_number:0, action_parameter:0 }, //0x03
	{   clock_cycle:4, machine_cycle:1, action:inc_b, action_bit_number:0, action_parameter:0 }, //0x04
	{   clock_cycle:4, machine_cycle:1, action:dec_b, action_bit_number:0, action_parameter:0 }, //0x05
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_b8, action_bit_number:8, action_parameter:1 }, //0x06 ld_b8
	{   clock_cycle:4, machine_cycle:1, action:rlca, action_bit_number:0, action_parameter:0 }, //0x07 
	{   clock_cycle:20, machine_cycle:5, action:(void (*)(unsigned int))LD_a16_sp, action_bit_number:16, action_parameter:2 }, //0x08 LD_a16_sp
	{   clock_cycle:8, machine_cycle:2, action:add_hl_bc, action_bit_number:0, action_parameter:0 }, //0x09
	{   clock_cycle:8, machine_cycle:2, action:ld_a_bc, action_bit_number:0, action_parameter:0 }, //0x0a
	{   clock_cycle:8, machine_cycle:2, action:dec_bc, action_bit_number:0, action_parameter:0 }, //0x0b
	{   clock_cycle:4, machine_cycle:1, action:inc_c, action_bit_number:0, action_parameter:0 }, //0x0c
	{   clock_cycle:4, machine_cycle:1, action:dec_c, action_bit_number:0, action_parameter:0 }, //0x0d
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_c8, action_bit_number:8, action_parameter:1 }, //0x0e ld_c8
	{   clock_cycle:4, machine_cycle:1, action:rrca, action_bit_number:0, action_parameter:0 }, //0x0f
	//{   clock_cycle:4, machine_cycle:1, action:nop, action_bit_number:0, action_parameter:0 }, //0x10
	//{   clock_cycle:4, machine_cycle:1, action:nop, action_bit_number:0, action_parameter:0 }, //0x11
	{   clock_cycle:4, machine_cycle:1, action:stop, action_bit_number:0, action_parameter:0 }, //0x10
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ld_de16, action_bit_number:16, action_parameter:2 }, //0x11 ld_de16
	{   clock_cycle:8, machine_cycle:2, action:ld_dea, action_bit_number:0, action_parameter:0 }, //0x12
	{   clock_cycle:8, machine_cycle:2, action:inc_de, action_bit_number:0, action_parameter:0 }, //0x13
	{   clock_cycle:4, machine_cycle:1, action:inc_d, action_bit_number:0, action_parameter:0 }, //0x14
	{   clock_cycle:4, machine_cycle:1, action:dec_d, action_bit_number:0, action_parameter:0 }, //0x15
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_d8, action_bit_number:8, action_parameter:1 }, //0x16 ld_d8
	{   clock_cycle:4, machine_cycle:1, action:rla, action_bit_number:0, action_parameter:0 }, //0x17 
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))jr_r8, action_bit_number:8, action_parameter:1 }, //0x18 jr_r8
	{   clock_cycle:8, machine_cycle:2, action:add_hl_de, action_bit_number:0, action_parameter:0 }, //0x19
	{   clock_cycle:8, machine_cycle:2, action:ld_a_de, action_bit_number:0, action_parameter:0 }, //0x1a
	{   clock_cycle:8, machine_cycle:2, action:dec_de, action_bit_number:0, action_parameter:0 }, //0x1b
	{   clock_cycle:4, machine_cycle:1, action:inc_e, action_bit_number:0, action_parameter:0 }, //0x1c
	{   clock_cycle:4, machine_cycle:1, action:dec_e, action_bit_number:0, action_parameter:0 }, //0x1d
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_e8, action_bit_number:1, action_parameter:1 }, //0x1e ld_e8
	{   clock_cycle:4, machine_cycle:1, action:rra, action_bit_number:0, action_parameter:0 }, //0x1f
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jr_nr8, action_bit_number:8, action_parameter:1 }, //0x20 jr_nr8
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ld_hl16, action_bit_number:16, action_parameter:2 }, //0x21 ld_hl16
	{   clock_cycle:8, machine_cycle:2, action:ld_hla, action_bit_number:0, action_parameter:0 }, //0x22
	{   clock_cycle:8, machine_cycle:2, action:inc_hl, action_bit_number:0, action_parameter:0 }, //0x23
	{   clock_cycle:4, machine_cycle:1, action:inc_h, action_bit_number:0, action_parameter:0 }, //0x24
	{   clock_cycle:4, machine_cycle:1, action:dec_h, action_bit_number:0, action_parameter:0 }, //0x25
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_h8, action_bit_number:8, action_parameter:1 }, //0x26 ld_h8
	{   clock_cycle:4, machine_cycle:1, action:DAA, action_bit_number:0, action_parameter:0 }, //0x27
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jr_zr8, action_bit_number:8, action_parameter:1 }, //0x28 jr_zr8
	{   clock_cycle:8, machine_cycle:2, action:add_hl_hl, action_bit_number:0, action_parameter:0 }, //0x29
	{   clock_cycle:8, machine_cycle:2, action:ld_a_hll, action_bit_number:0, action_parameter:0 }, //0x2a
	{   clock_cycle:8, machine_cycle:2, action:dec_hl, action_bit_number:0, action_parameter:0 }, //0x2b
	{   clock_cycle:4, machine_cycle:1, action:inc_l, action_bit_number:0, action_parameter:0 }, //0x2c
	{   clock_cycle:4, machine_cycle:1, action:dec_l, action_bit_number:0, action_parameter:0 }, //0x2d
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_l8, action_bit_number:8, action_parameter:1 }, //0x2e ld_l8
	{   clock_cycle:4, machine_cycle:1, action:cpl, action_bit_number:0, action_parameter:0 }, //0x2f
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jr_ncr8, action_bit_number:8, action_parameter:1 }, //0x30 jr_ncr8
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ld_sp16, action_bit_number:16, action_parameter:2 }, //0x31 ld_sp16
	{   clock_cycle:8, machine_cycle:2, action:ld_hlma, action_bit_number:0, action_parameter:0 }, //0x32
	{   clock_cycle:8, machine_cycle:2, action:inc_sp, action_bit_number:0, action_parameter:0 }, //0x33
	{   clock_cycle:12, machine_cycle:3, action:inc_hlm, action_bit_number:0, action_parameter:0 }, //0x34
	{   clock_cycle:12, machine_cycle:3, action:dec_hlm, action_bit_number:0, action_parameter:0 }, //0x35
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ld_hlld8, action_bit_number:8, action_parameter:1 }, //0x36 ld_hlld8
	{   clock_cycle:4, machine_cycle:1, action:scf, action_bit_number:0, action_parameter:0 }, //0x37
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jr_cr8, action_bit_number:8, action_parameter:1 }, //0x38 jr_cr8
	{   clock_cycle:8, machine_cycle:2, action:add_hl_SP, action_bit_number:0, action_parameter:0 }, //0x39
	{   clock_cycle:8, machine_cycle:2, action:ld_a_hlm, action_bit_number:0, action_parameter:0 }, //0x3a
	{   clock_cycle:8, machine_cycle:2, action:dec_sp, action_bit_number:0, action_parameter:0 }, //0x3b
	{   clock_cycle:4, machine_cycle:1, action:inc_a, action_bit_number:0, action_parameter:0 }, //0x3c
	{   clock_cycle:4, machine_cycle:1, action:dec_a, action_bit_number:0, action_parameter:0 }, //0x3d
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))ld_a8, action_bit_number:8, action_parameter:1 }, //0x3e
	{   clock_cycle:4, machine_cycle:1, action:CCF, action_bit_number:0, action_parameter:0 }, //0x3f
	{   clock_cycle:8, machine_cycle:2, action:ld_b_b, action_bit_number:0, action_parameter:0 }, //0x40
	{   clock_cycle:4, machine_cycle:1, action:ld_b_c, action_bit_number:0, action_parameter:0 }, //0x41
	{   clock_cycle:4, machine_cycle:1, action:ld_b_d, action_bit_number:0, action_parameter:0 }, //0x42
	{   clock_cycle:4, machine_cycle:1, action:ld_b_e, action_bit_number:0, action_parameter:0 }, //0x43
	{   clock_cycle:4, machine_cycle:1, action:ld_b_h, action_bit_number:0, action_parameter:0 }, //0x44
	{   clock_cycle:4, machine_cycle:1, action:ld_b_l, action_bit_number:0, action_parameter:0 }, //0x45
	{   clock_cycle:8, machine_cycle:2, action:ld_b_hl, action_bit_number:0, action_parameter:0 }, //0x46
	{   clock_cycle:4, machine_cycle:1, action:ld_b_a, action_bit_number:0, action_parameter:0 }, //0x47
	{   clock_cycle:4, machine_cycle:1, action:ld_c_b, action_bit_number:0, action_parameter:0 }, //0x48
	{   clock_cycle:4, machine_cycle:1, action:ld_c_c, action_bit_number:0, action_parameter:0 }, //0x49
	{   clock_cycle:4, machine_cycle:1, action:ld_c_d, action_bit_number:0, action_parameter:0 }, //0x4a
	{   clock_cycle:4, machine_cycle:1, action:ld_c_e, action_bit_number:0, action_parameter:0 }, //0x4b
	{   clock_cycle:4, machine_cycle:1, action:ld_c_h, action_bit_number:0, action_parameter:0 }, //0x4c
	{   clock_cycle:4, machine_cycle:1, action:ld_c_l, action_bit_number:0, action_parameter:0 }, //0x4d
	{   clock_cycle:8, machine_cycle:2, action:ld_c_hl, action_bit_number:0, action_parameter:0 }, //0x4e
	{   clock_cycle:4, machine_cycle:1, action:ld_c_a, action_bit_number:0, action_parameter:0 }, //0x4f
	{   clock_cycle:4, machine_cycle:1, action:ld_d_b, action_bit_number:0, action_parameter:0 }, //0x50
	{   clock_cycle:4, machine_cycle:1, action:ld_d_c, action_bit_number:0, action_parameter:0 }, //0x51
	{   clock_cycle:4, machine_cycle:1, action:ld_d_d, action_bit_number:0, action_parameter:0 }, //0x52
	{   clock_cycle:4, machine_cycle:1, action:ld_d_e, action_bit_number:0, action_parameter:0 }, //0x53
	{   clock_cycle:4, machine_cycle:1, action:ld_d_h, action_bit_number:0, action_parameter:0 }, //0x54
	{   clock_cycle:4, machine_cycle:1, action:ld_d_l, action_bit_number:0, action_parameter:0 }, //0x55
	{   clock_cycle:8, machine_cycle:2, action:ld_d_hl, action_bit_number:0, action_parameter:0 }, //0x56
	{   clock_cycle:4, machine_cycle:1, action:ld_d_a, action_bit_number:0, action_parameter:0 }, //0x57
	{   clock_cycle:4, machine_cycle:1, action:ld_e_b, action_bit_number:0, action_parameter:0 }, //0x58
	{   clock_cycle:4, machine_cycle:1, action:ld_e_c, action_bit_number:0, action_parameter:0 }, //0x59
	{   clock_cycle:4, machine_cycle:1, action:ld_e_d, action_bit_number:0, action_parameter:0 }, //0x5a
	{   clock_cycle:4, machine_cycle:1, action:ld_e_e, action_bit_number:0, action_parameter:0 }, //0x5b
	{   clock_cycle:4, machine_cycle:1, action:ld_e_h, action_bit_number:0, action_parameter:0 }, //0x5c
	{   clock_cycle:4, machine_cycle:1, action:ld_e_l, action_bit_number:0, action_parameter:0 }, //0x5d
	{   clock_cycle:8, machine_cycle:2, action:ld_e_hl, action_bit_number:0, action_parameter:0 }, //0x5e
	{   clock_cycle:4, machine_cycle:1, action:ld_e_a, action_bit_number:0, action_parameter:0 }, //0x5f
	{   clock_cycle:4, machine_cycle:1, action:ld_h_b, action_bit_number:0, action_parameter:0 }, //0x60
	{   clock_cycle:4, machine_cycle:1, action:ld_h_c, action_bit_number:0, action_parameter:0 }, //0x61
	{   clock_cycle:4, machine_cycle:1, action:ld_h_d, action_bit_number:0, action_parameter:0 }, //0x62
	{   clock_cycle:4, machine_cycle:1, action:ld_h_e, action_bit_number:0, action_parameter:0 }, //0x63
	{   clock_cycle:4, machine_cycle:1, action:ld_h_h, action_bit_number:0, action_parameter:0 }, //0x64
	{   clock_cycle:4, machine_cycle:1, action:ld_h_l, action_bit_number:0, action_parameter:0 }, //0x65
	{   clock_cycle:8, machine_cycle:2, action:ld_h_hl, action_bit_number:0, action_parameter:0 }, //0x66
	{   clock_cycle:4, machine_cycle:1, action:ld_h_a, action_bit_number:0, action_parameter:0 }, //0x67
	{   clock_cycle:4, machine_cycle:1, action:ld_l_b, action_bit_number:0, action_parameter:0 }, //0x68
	{   clock_cycle:4, machine_cycle:1, action:ld_l_c, action_bit_number:0, action_parameter:0 }, //0x69
	{   clock_cycle:4, machine_cycle:1, action:ld_l_d, action_bit_number:0, action_parameter:0 }, //0x6a
	{   clock_cycle:4, machine_cycle:1, action:ld_l_e, action_bit_number:0, action_parameter:0 }, //0x6b
	{   clock_cycle:4, machine_cycle:1, action:ld_l_h, action_bit_number:0, action_parameter:0 }, //0x6c
	{   clock_cycle:4, machine_cycle:1, action:ld_l_l, action_bit_number:0, action_parameter:0 }, //0x6d
	{   clock_cycle:8, machine_cycle:2, action:ld_l_hl, action_bit_number:0, action_parameter:0 }, //0x6e
	{   clock_cycle:4, machine_cycle:1, action:ld_l_a, action_bit_number:0, action_parameter:0 }, //0x6f
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_b, action_bit_number:0, action_parameter:0 }, //0x70
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_c, action_bit_number:0, action_parameter:0 }, //0x71
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_d, action_bit_number:0, action_parameter:0 }, //0x72
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_e, action_bit_number:0, action_parameter:0 }, //0x73
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_h, action_bit_number:0, action_parameter:0 }, //0x74
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_l, action_bit_number:0, action_parameter:0 }, //0x75
	{   clock_cycle:4, machine_cycle:1, action:halt, action_bit_number:0, action_parameter:0 }, //0x76
	{   clock_cycle:8, machine_cycle:2, action:ld_hl_a, action_bit_number:0, action_parameter:0 }, //0x77
	{   clock_cycle:4, machine_cycle:1, action:ld_a_b, action_bit_number:0, action_parameter:0 }, //0x78
	{   clock_cycle:4, machine_cycle:1, action:ld_a_c, action_bit_number:0, action_parameter:0 }, //0x79
	{   clock_cycle:4, machine_cycle:1, action:ld_a_d, action_bit_number:0, action_parameter:0 }, //0x7a
	{   clock_cycle:4, machine_cycle:1, action:ld_a_e, action_bit_number:0, action_parameter:0 }, //0x7b
	{   clock_cycle:4, machine_cycle:1, action:ld_a_h, action_bit_number:0, action_parameter:0 }, //0x7c
	{   clock_cycle:4, machine_cycle:1, action:ld_a_l, action_bit_number:0, action_parameter:0 }, //0x7d
	{   clock_cycle:8, machine_cycle:2, action:ld_a_hl, action_bit_number:0, action_parameter:0 }, //0x7e
	{   clock_cycle:4, machine_cycle:1, action:ld_a_a, action_bit_number:0, action_parameter:0 }, //0x7f
	{   clock_cycle:4, machine_cycle:1, action:add_a_b, action_bit_number:0, action_parameter:0 }, //0x80
	{   clock_cycle:4, machine_cycle:1, action:add_a_c, action_bit_number:0, action_parameter:0 }, //0x81
	{   clock_cycle:4, machine_cycle:1, action:add_a_d, action_bit_number:0, action_parameter:0 }, //0x82
	{   clock_cycle:4, machine_cycle:1, action:add_a_e, action_bit_number:0, action_parameter:0 }, //0x83
	{   clock_cycle:4, machine_cycle:1, action:add_a_h, action_bit_number:0, action_parameter:0 }, //0x84
	{   clock_cycle:4, machine_cycle:1, action:add_a_l, action_bit_number:0, action_parameter:0 }, //0x85
	{   clock_cycle:8, machine_cycle:2, action:add_a_hl, action_bit_number:0, action_parameter:0 }, //0x86
	{   clock_cycle:4, machine_cycle:1, action:add_a_a, action_bit_number:0, action_parameter:0 }, //0x87
	{   clock_cycle:4, machine_cycle:1, action:adc_a_b, action_bit_number:0, action_parameter:0 }, //0x88
	{   clock_cycle:4, machine_cycle:1, action:adc_a_c, action_bit_number:0, action_parameter:0 }, //0x89
	{   clock_cycle:4, machine_cycle:1, action:adc_a_d, action_bit_number:0, action_parameter:0 }, //0x8a
	{   clock_cycle:4, machine_cycle:1, action:adc_a_e, action_bit_number:0, action_parameter:0 }, //0x8b
	{   clock_cycle:4, machine_cycle:1, action:adc_a_h, action_bit_number:0, action_parameter:0 }, //0x8c
	{   clock_cycle:4, machine_cycle:1, action:adc_a_l, action_bit_number:0, action_parameter:0 }, //0x8d
	{   clock_cycle:8, machine_cycle:2, action:adc_a_hl, action_bit_number:0, action_parameter:0 }, //0x8e
	{   clock_cycle:4, machine_cycle:1, action:adc_a_a, action_bit_number:0, action_parameter:0 }, //0x8f
	{   clock_cycle:4, machine_cycle:1, action:sub_a_b, action_bit_number:0, action_parameter:0 }, //0x90
	{   clock_cycle:4, machine_cycle:1, action:sub_a_c, action_bit_number:0, action_parameter:0 }, //0x91
	{   clock_cycle:4, machine_cycle:1, action:sub_a_d, action_bit_number:0, action_parameter:0 }, //0x92
	{   clock_cycle:4, machine_cycle:1, action:sub_a_e, action_bit_number:0, action_parameter:0 }, //0x93
	{   clock_cycle:4, machine_cycle:1, action:sub_a_h, action_bit_number:0, action_parameter:0 }, //0x94
	{   clock_cycle:4, machine_cycle:1, action:sub_a_l, action_bit_number:0, action_parameter:0 }, //0x95
	{   clock_cycle:8, machine_cycle:2, action:sub_a_hl, action_bit_number:0, action_parameter:0 }, //0x96
	{  4, 1,sub_a_a, action_bit_number:0, action_parameter:0 }, //0x97
	{   clock_cycle:4, machine_cycle:1, action:sbc_a_b, action_bit_number:0, action_parameter:0 }, //0x98
	{   clock_cycle:4, machine_cycle:1, action:sbc_a_c, action_bit_number:0, action_parameter:0 }, //0x99
	{   clock_cycle:4, machine_cycle:1, action:sbc_a_d, action_bit_number:0, action_parameter:0 }, //0x9a
	{   clock_cycle:4, machine_cycle:1, action:sbc_a_e, action_bit_number:0, action_parameter:0 }, //0x9b
	{   clock_cycle:4, machine_cycle:1, action:sbc_a_h, action_bit_number:0, action_parameter:0 }, //0x9c
	{   clock_cycle:4, machine_cycle:1, action:sbc_a_l, action_bit_number:0, action_parameter:0 }, //0x9d
	{   clock_cycle:8, machine_cycle:2, action:sbc_a_hl, action_bit_number:0, action_parameter:0 }, //0x9e
	{  4, 1,sbc_a_a, action_bit_number:0, action_parameter:0 }, //0x9f
	{   clock_cycle:4, machine_cycle:1, action:and_b, action_bit_number:0, action_parameter:0 }, //0xa0
	{   clock_cycle:4, machine_cycle:1, action:and_c, action_bit_number:0, action_parameter:0 }, //0xa1
	{   clock_cycle:4, machine_cycle:1, action:and_d, action_bit_number:0, action_parameter:0 }, //0xa2
	{   clock_cycle:4, machine_cycle:1, action:and_e, action_bit_number:0, action_parameter:0 }, //0xa3
	{   clock_cycle:4, machine_cycle:1, action:and_h, action_bit_number:0, action_parameter:0 }, //0xa4
	{   clock_cycle:4, machine_cycle:1, action:and_l, action_bit_number:0, action_parameter:0 }, //0xa5
	{   clock_cycle:8, machine_cycle:2, action:and_hlp, action_bit_number:0, action_parameter:0 }, //0xa6
	{  4, 1,and_a, action_bit_number:0, action_parameter:0 }, //0xa7
	{   clock_cycle:4, machine_cycle:1, action:xor_b, action_bit_number:0, action_parameter:0 }, //0xa8
	{   clock_cycle:4, machine_cycle:1, action:xor_c, action_bit_number:0, action_parameter:0 }, //0xa9
	{   clock_cycle:4, machine_cycle:1, action:xor_d, action_bit_number:0, action_parameter:0 }, //0xaa
	{   clock_cycle:4, machine_cycle:1, action:xor_e, action_bit_number:0, action_parameter:0 }, //0xab
	{   clock_cycle:4, machine_cycle:1, action:xor_h, action_bit_number:0, action_parameter:0 }, //0xac
	{   clock_cycle:4, machine_cycle:1, action:xor_l, action_bit_number:0, action_parameter:0 }, //0xad
	{   clock_cycle:8, machine_cycle:2, action:xor_hlp, action_bit_number:0, action_parameter:0 }, //0xae
	{  4, 1,xor_a, action_bit_number:0, action_parameter:0 }, //0xaf
	{   clock_cycle:4, machine_cycle:1, action:or_b, action_bit_number:0, action_parameter:0 }, //0xb0
	{   clock_cycle:4, machine_cycle:1, action:or_c, action_bit_number:0, action_parameter:0 }, //0xb1
	{   clock_cycle:4, machine_cycle:1, action:or_d, action_bit_number:0, action_parameter:0 }, //0xb2
	{   clock_cycle:4, machine_cycle:1, action:or_e, action_bit_number:0, action_parameter:0 }, //0xb3
	{   clock_cycle:4, machine_cycle:1, action:or_h, action_bit_number:0, action_parameter:0 }, //0xb4
	{   clock_cycle:4, machine_cycle:1, action:or_l, action_bit_number:0, action_parameter:0 }, //0xb5
	{   clock_cycle:8, machine_cycle:2, action:or_hlp, action_bit_number:0, action_parameter:0 }, //0xb6
	{  4, 1,or_a, action_bit_number:0, action_parameter:0 }, //0xb7
	{   clock_cycle:4, machine_cycle:1, action:cp_b, action_bit_number:0, action_parameter:0 }, //0xb8
	{   clock_cycle:4, machine_cycle:1, action:cp_c, action_bit_number:0, action_parameter:0 }, //0xb9
	{   clock_cycle:4, machine_cycle:1, action:cp_d, action_bit_number:0, action_parameter:0 }, //0xba
	{   clock_cycle:4, machine_cycle:1, action:cp_e, action_bit_number:0, action_parameter:0 }, //0xbb
	{   clock_cycle:4, machine_cycle:1, action:cp_h, action_bit_number:0, action_parameter:0 }, //0xbc
	{   clock_cycle:4, machine_cycle:1, action:cp_l, action_bit_number:0, action_parameter:0 }, //0xbd
	{   clock_cycle:8, machine_cycle:2, action:cp_hlp, action_bit_number:0, action_parameter:0 }, //0xbe
	{  4, 1,cp_a, action_bit_number:0, action_parameter:0 }, //0xbf
	{   clock_cycle:0, machine_cycle:0, action:ret_nz, action_bit_number:0, action_parameter:0 }, //0xc0
	{   clock_cycle:12, machine_cycle:3, action:pop_bc, action_bit_number:0, action_parameter:0 }, //0xc1
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jp_nz_a16, action_bit_number:16, action_parameter:2}, //0xc2 Ver como pasar parametros jp_nz_a16
	{   clock_cycle:16, machine_cycle:4, action:(void (*)(unsigned int))jp_a16, action_bit_number:16, action_parameter:2 }, //0xc3 jp_a16
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))call_nz_a16, action_bit_number:16, action_parameter:2 }, //0xc4 call_nz_a16
	{   clock_cycle:16, machine_cycle:4, action:push_bc, action_bit_number:0, action_parameter:0 }, //0xc5
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))add_a_d8, action_bit_number:8, action_parameter:1 }, //0xc6 add_a_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_00h, action_bit_number:0, action_parameter:0 }, //0xc7
	{   clock_cycle:0, machine_cycle:0, action:ret_z, action_bit_number:0, action_parameter:0 }, //0xc8
	{   clock_cycle:16, machine_cycle:4, action:ret, action_bit_number:0, action_parameter:0 }, //0xc9
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jp_z_a16, action_bit_number:16, action_parameter:2 }, //0xca jp_z_a16
	{   clock_cycle:4, machine_cycle:1, action:nada, action_bit_number:0, action_parameter:0 }, //0xcb
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))call_z_a16, action_bit_number:16, action_parameter:2 }, //0xcc call_z_a16
	{   clock_cycle:24, machine_cycle:6, action:(void (*)(unsigned int))call_a16, action_bit_number:16, action_parameter:2 }, //0xcd call_a16
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))adc_a_d8, action_bit_number:8, action_parameter:1 }, //0xce adc_a_d8
	{   clock_cycle:16, machine_cycle:4, action:RST_08H, action_bit_number:0, action_parameter:0 }, //0xcf
	{   clock_cycle:0, machine_cycle:0, action:ret_nc, action_bit_number:0, action_parameter:0 }, //0xd0
	{   clock_cycle:12, machine_cycle:3, action:pop_de, action_bit_number:0, action_parameter:0 }, //0xd1
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jp_nc_a16, action_bit_number:16, action_parameter:2 }, //0xd2 jp_nc_a16
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xd3
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))call_nc_a16, action_bit_number:16, action_parameter:2 }, //0xd4 call_nc_a16
	{   clock_cycle:12, machine_cycle:3, action:push_de, action_bit_number:0, action_parameter:0 }, //0xd5
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))sub_d8, action_bit_number:8, action_parameter:1 }, //0xd6 sub_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_10h, action_bit_number:0, action_parameter:0 }, //0xd7
	{   clock_cycle:0, machine_cycle:0, action:ret_c, action_bit_number:0, action_parameter:0 }, //0xd8
	{   clock_cycle:16, machine_cycle:4, action:reti, action_bit_number:0, action_parameter:0 }, //0xd9
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))jp_c_a16, action_bit_number:16, action_parameter:2 }, //0xda jp_c_a16
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xdb
	{   clock_cycle:0, machine_cycle:0, action:(void (*)(unsigned int))call_c_a16, action_bit_number:16, action_parameter:2 }, //0xdc call_c_a16
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xdd
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))sbc_a_d8, action_bit_number:8, action_parameter:1 }, //0xde sbc_a_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_18h, action_bit_number:0, action_parameter:0 }, //0xdf
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ldh_a8_a, action_bit_number:8, action_parameter:1 }, //0xe0 ldh_a8_a
	{   clock_cycle:12, machine_cycle:3, action:pop_hl, action_bit_number:0, action_parameter:0 }, //0xe1
	{   clock_cycle:8, machine_cycle:2, action:ld_ca, action_bit_number:0, action_parameter:0 }, //0xe2
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xe3
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xe4
	{   clock_cycle:16, machine_cycle:4, action:push_hl, action_bit_number:0, action_parameter:0 }, //0xe5
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))and_d8, action_bit_number:8, action_parameter:1 }, //0xe6 and_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_20h, action_bit_number:0, action_parameter:0 }, //0xe7
	{   clock_cycle:16, machine_cycle:4, action:(void (*)(unsigned int))add_sp_r8, action_bit_number:8, action_parameter:1 }, //0xe8 add_sp_r8
	{   clock_cycle:4, machine_cycle:1, action:jp_hl, action_bit_number:0, action_parameter:0 }, //0xe9
	{   clock_cycle:16, machine_cycle:4, action:(void (*)(unsigned int))ld_a16_a, action_bit_number:16, action_parameter:2 }, //0xea ld_a16_a
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xeb
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xec
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xed
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))xor_d8, action_bit_number:8, action_parameter:1 }, //0xee xor_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_28h, action_bit_number:0, action_parameter:0 }, //0xef
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ldh_a_a8, action_bit_number:8, action_parameter:1 }, //0xf0 ldh_a_a8
	{   clock_cycle:12, machine_cycle:3, action:pop_af, action_bit_number:0, action_parameter:0 }, //0xf1
	{   clock_cycle:8, machine_cycle:2, action:la_ac, action_bit_number:0, action_parameter:0 }, //0xf2
	{   clock_cycle:4, machine_cycle:1, action:di, action_bit_number:0, action_parameter:0 }, //0xf3
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xf4
	{   clock_cycle:16, machine_cycle:4, action:push_af, action_bit_number:0, action_parameter:0 }, //0xf5
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))or_d8, action_bit_number:8, action_parameter:1 }, //0xf6 or_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_30h, action_bit_number:0, action_parameter:0 }, //0xf7
	{   clock_cycle:12, machine_cycle:3, action:(void (*)(unsigned int))ld_hl_spr8, action_bit_number:8, action_parameter:1 }, //0xf8 ld_hl_spr8
	{   clock_cycle:8, machine_cycle:2, action:ld_sp_hl, action_bit_number:0, action_parameter:0 }, //0xf9
	{   clock_cycle:16, machine_cycle:4, action:(void (*)(unsigned int))ld_a_a16, action_bit_number:16, action_parameter:2 }, //0xfa ld_a_a16
	{   clock_cycle:4, machine_cycle:1, action:ei, action_bit_number:0, action_parameter:0 }, //0xfb
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xfc
	{   clock_cycle:0, machine_cycle:0, action:nada, action_bit_number:0, action_parameter:0 }, //0xfd
	{   clock_cycle:8, machine_cycle:2, action:(void (*)(unsigned int))cp_d8, action_bit_number:8, action_parameter:1 }, //0xfe cp_d8
	{   clock_cycle:16, machine_cycle:4, action:rst_38h, action_bit_number:0, action_parameter:0 } //0xff

};
/*struct registros{
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
}regist;*/

void reset () {
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

void reconstruirHL () {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
}

void deconstruirHL () {
	regist.H=(unsigned char) ((regist.HL >>8) & 0xFF);
	regist.L=(unsigned char) (regist.HL & 0xFF);
}

void reconstruirDE () {
	regist.DE=regist.D;
	regist.DE=regist.DE<<8;
	regist.DE=regist.DE|regist.E;
}

void deconstruirDE () {
	regist.D=(unsigned char) ((regist.DE >>8) & 0xFF);
	regist.E=(unsigned char) (regist.DE & 0xFF);
}

void reconstruirBC () {
	regist.BC=regist.B;
	regist.BC=regist.BC<<8;
	regist.BC=regist.BC|regist.C;
}

void deconstruirBC () {
	regist.B=(unsigned char) ((regist.BC >>8) & 0xFF);
	regist.C=(unsigned char) (regist.BC & 0xFF);
}

int machine_cycle=0;
int clock_cycle=0;

int interrrupt_enable=0;

void keyboardInterrupt(int signal){
	if(signal==SIGINT){
		interrrupt_enable=1;
		printf("probar señal ¿TECLADO?");

	}

}

//funcion para indicar que ha habido acarreo
static void acarreo () {
	//activar flag con OR
	regist.F= regist.F | 0x10;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0xEF;

}

//HALF CARRY
static void half () {
		//activar flag con OR
	regist.F= regist.F | 0x20;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0xDF;
}

//SUBSTRACT N
static void SUBSTRACT () {
	//activar flag con OR
	regist.F= regist.F | 0x40;

	//TRATARLO?

	//desactivar flag con una AND
	regist.F= regist.F & 0xBF;

}

//ZERO
static void zero () {
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

//incrementar de lo que coges de memoria y soy muy vago para cambiar lo que recibe la otra funcion
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

//suma para registros de 16bits, ahora electric boogaloo
static void suma2(char16_t *A, char16_t B){
	char32_t carry= *A + B;

	//para comprobar el half
	char16_t half1=*A & 0xFF;
	char16_t half2=B & 0xFF;
	char16_t half3=half1 + half2;

	*A=(char16_t) (carry & 0xFFFF);

	if((carry >> 16) > 0x01){
		regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	//MUY POTENTE FALLO AQUI
	if((half3>>8) >=0x01){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	
	regist.F= regist.F &  0xBF; //desactivar el flag N
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
	regist.F= regist.F & 0xDF;//desactiva el half
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
	regist.F= regist.F & 0xDF;//desactiva el half
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
void nop (unsigned int) {
	clock_cycle+=4;
	machine_cycle++;
}

//LD BC, d16 0x01 Carga inmediata de 16 bits a BC
void ld_bc16(char16_t valor){
	regist.BC= valor;
	deconstruirBC();
}

//LD (BC), A, 0x02 guardar el valor de A en la direccion de BC
void ld_bca (unsigned int) {
	writeMEMB(regist.BC,regist.A);
}

// 0x03
void inc_bc (unsigned int) { 
	reconstruirBC();
	regist.BC=regist.BC + 0x01;
	deconstruirBC(); 
} //en estas no se comprueban flags

// 0x04
void inc_b (unsigned int) {
	inc(&regist.B);
	reconstruirBC();
}

// 0x05
void dec_b (unsigned int) { 
	dec(&regist.B);
	reconstruirBC();
}

//LD B, d8, 0x06 carga inmediata de valor de 8 bits en B
void ld_b8(unsigned char valor){
	regist.B=valor;
	reconstruirBC();
}

//RLCA 0x07 rota A un bit a la izquierda, y si el bit mas significativo es 1 activas el flag de carry
void rlca (unsigned int) {
	//coges el bit mas significativo y lo dejas a la izquierda, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = regist.A >> 7;
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	regist.A= regist.A << 1;
	//como es una rotacion, se le mete al final lo que "salio"
	regist.A += u;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(regist.A==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

}

//LD (a16), SP, 0x08 Guarda el valor de SP en la direccion inmediata de 16bits
void LD_a16_sp(char16_t direccion){
	writeMEM16(direccion, regist.SP);
}

//ADD HL, BC, 0x09 suma dos valores de 16 bits y lo guarda en HL
void add_hl_bc (unsigned int) {
	reconstruirBC();
	reconstruirHL();
	suma2(&regist.HL, regist.BC);
	deconstruirHL();
}

//LD a,(BC), 0x0a carga el valor de BC y lo mete en A
void ld_a_bc (unsigned int) { 
	//hacer esto en la futura funcion loadMEM
	regist.BC=regist.B;
	regist.BC=regist.BC<<8;
	regist.BC=regist.BC|regist.C;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.A = loadMEMB(regist.BC);
	
}  

// 0x0b
void dec_bc (unsigned int) { 
	reconstruirBC();
	regist.BC=regist.BC - 0x01;
	deconstruirBC(); 
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x0c
void inc_c (unsigned int) { 
	inc(&regist.C); 
	reconstruirBC();	
}

// 0x0d
void dec_c (unsigned int) { 
	dec(&regist.C);
	reconstruirBC();

}

//LD C, d8, 0x0e carga inmediata de valor de 8 bits en B
void ld_c8(unsigned char valor){
	regist.C=valor;
	reconstruirBC();
}

//RRCA, 0x0F rota A un bit a la derecha, y si el bit menos significativo es 1 activas el flag de carry
void rrca (unsigned int) {
	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = regist.A & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	regist.A= regist.A >> 1;
	//como es una rotacion, se le mete por el otro lado lo que salio
	regist.A += u << 7;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(regist.A==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

}

//STOP 0x10 para la CPU y la pantalla hasta que se presione un boton
void stop (unsigned int) {
	//clock_cycle+=4;
	//machine_cycle++;
	//STOPGPU();
	while(!interrrupt_enable){
		pause();

	}

}

//LD DE, d16 0x11 Carga inmediata de 16 bits a DE
void ld_de16(char16_t valor){
	regist.DE= valor;
	deconstruirDE();
}

//LD (DE), A, 0x12 guardar el valor de A en la direccion de DE
void ld_dea (unsigned int) {
	reconstruirDE();
	writeMEMB(regist.DE,regist.A);
}

// 0x13
void inc_de (unsigned int) { 
	reconstruirDE();
	regist.DE=regist.DE + 0x01; 
	deconstruirDE();
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x14
void inc_d (unsigned int) {
	inc(&regist.D);
	reconstruirDE();
}

// 0x15
void dec_d (unsigned int) {
	dec(&regist.D);
	reconstruirDE();	
}

//LD D, d8, 0x16 carga inmediata de valor de 8 bits en D
void ld_d8(unsigned char valor){
	regist.D=valor;
	reconstruirDE();
}

//RLA 0x17 rotar A un bit a la izquierda, el mas significativo es el nuevo valor del flag carry y el antiguo valor es el bit menos significativo de a
void rla (unsigned int) {
	//cogemos el valor del bit de carry
	unsigned char bit=regist.F & 0x10;
	bit= bit >>4;
	bit= bit & 0x01;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	//vemos si el mas significativo de A es 1 o 0
	unsigned char u = regist.A >> 7;
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	regist.A = regist.A << 1;

	//como es una rotacion, se le mete al final lo que "salio"
	regist.A += bit;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(regist.A==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

}

//JR r8 0x18 incrementa en un byte signed inmediato PC
void jr_r8(char valor){
	regist.PC += (signed char) valor; 
}

//ADD HL, DE, 0x19
void add_hl_de (unsigned int) {
	reconstruirDE();
	reconstruirHL();
	suma2(&regist.HL, regist.DE);
	deconstruirHL();
}

//LD a,(DE), 0x1a
void ld_a_de (unsigned int) { 
	regist.DE=regist.D;
	regist.DE=regist.DE<<8;
	regist.DE=regist.DE|regist.E;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.A = loadMEMB(regist.DE);
	
}  

// 0x1b
void dec_de (unsigned int) { 
	reconstruirDE();
	regist.DE=regist.DE - 0x01;
	deconstruirDE();
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x1c
void inc_e (unsigned int) {
	inc(&regist.E); 
	reconstruirDE();
}

// 0x1d
void dec_e (unsigned int) {
	dec(&regist.E); 
	reconstruirHL();
}

//LD E, d8, 0x1e
void ld_e8(unsigned char valor){
	regist.E=valor;
	reconstruirDE();
}

//RRA 0x1f, rotas A un bit a la derecha, el bit menos significativo pasa a ser el bit de carry y el antiguo valor es el mas significativo
void rra (unsigned int) {
	//cogemos el valor del bit de carry
	unsigned char bit=regist.F & 0x10;
	bit= bit <<3;
	bit= bit & 0x80;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa

	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = regist.A & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	regist.A = regist.A >> 1;

	//como es una rotacion, se le mete al final lo que "salio"
	regist.A += bit;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(regist.A==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

}

//JR NZ,r8, 0x20 branch si no es ZERO y le suma un signed byte a PC
void jr_nr8(char valor){
	unsigned char u = regist.F >> 7;
	if(u== 1){
		machine_cycle+=8;
	}else{
		regist.PC+= (signed char) valor;
		
		machine_cycle=+12;
	}
}

//LD HL, d16, 0x21
void ld_hl16(char16_t valor){
	regist.HL= valor;
	deconstruirHL();
}

//LD (HL+), A, 0x22
void ld_hla (unsigned int) {
	reconstruirDE();
	writeMEMB((regist.DE + 0x01),regist.A);
}

// 0x23
void inc_hl (unsigned int) {  
	reconstruirHL();
	regist.HL=regist.HL + 0x01;
	deconstruirHL();
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x24
void inc_h (unsigned int) { 
	inc(&regist.H); 
	reconstruirHL();

}

// 0x25
void dec_h (unsigned int) { 
	dec(&regist.H);
	reconstruirHL();
}

//LD H, d8, 0x26
void ld_h8(unsigned char valor){
	regist.H=valor;
	reconstruirHL();
}

//DAA, 0x27
void DAA (unsigned int) {
	unsigned short carry= regist.A;
	//esta operacion se hace justo despues de una suma o resta, y como siempre se cambia el flag N al hace una u otra (coge el valor 0 al sumar y 1 al restar)
	unsigned char flagN= (regist.F >> 6) & 0x01;
	unsigned char flagH= (regist.F >> 5) & 0x01;
	unsigned char flagC= (regist.F >> 4) & 0x01;
	if(flagN== 0){
		if((regist.A & 0x0F) > 0x09  || flagH == 1){
			carry += 0x06; 
		}
		if(flagC ==1 || regist.A > 0x99){
			carry+=0x60;
		}

	}else{
		if(flagC ==1){
			carry-=0x60;
		}
		if(flagH==1){
			carry-=0x06;
		}
	}
	
	regist.A= carry;
	

	if(regist.A== 0){
	regist.F= regist.F | 0x80;//flag ZERO
	}
	else{
		regist.F= regist.F & 0x7F;//desactivar ZERO	
	}
	if(carry > 0xFF){ //activar carry
		regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;
	}
	regist.F= regist.F & 0xDF;//desactiva el half
}

//JR Z, r8, 0x28 branch si el flag ZERO es 1
void jr_zr8( char valor){
	unsigned char u = regist.F >> 7;
	if(u== 1){
		regist.PC+= (signed char) valor;
		
		machine_cycle=+12;
	}else{
		
		machine_cycle+=8;
	}
}

//ADD HL, HL, 0x29
void add_hl_hl (unsigned int) {
	reconstruirHL();
	suma2(&regist.HL, regist.HL);
	deconstruirHL();
}

//LD A,(HL+), 0x2a
void ld_a_hll (unsigned int) { 
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.A = loadMEMB((regist.HL+ 0x01));
	
}  

// 0x2b
void dec_hl (unsigned int) { 
	reconstruirHL();
	regist.HL=regist.HL - 0x01;
	deconstruirHL(); 
} //en estas no se comprueban flags(las que trabajan con registros de 16 bits)

// 0x2c
void inc_l (unsigned int) { 
	inc(&regist.L); 
	reconstruirHL();
}

// 0x2d
void dec_l (unsigned int) { 
	dec(&regist.L); 
	reconstruirHL();
}

//LD L,d8, 0x2e
void ld_l8(unsigned char valor){
	regist.L=valor;
	reconstruirHL();
}

//CPL, 0x2f
void cpl (unsigned int) {
	regist.A= ~regist.A;

	regist.F= regist.F | 0x20; //activar half
	regist.F= regist.F | 0x40; //activar N
}

//JR NC, r8, 0x30 branch si el flag de carry es 0
void jr_ncr8(char valor){
	unsigned char u = regist.F >> 4 & 0x01;
	if(u== 1){
		machine_cycle+=8;
	}else{
		regist.PC+= (signed char) valor;
		
		machine_cycle=+12;
	}
}

//LD SP, d16, 0x31
void ld_sp16(char16_t valor){
	regist.SP= valor;
}

//LD (HL-),A 0x32
void ld_hlma (unsigned int) {
	reconstruirHL();
	writeMEMB(regist.HL,regist.A);
	regist.HL-= 0x01;
	deconstruirHL();
}

// 0x33
void inc_sp (unsigned int) { regist.SP++; }

// 0x34
void inc_hlm (unsigned int) {
	reconstruirHL();
	char16_t patata=regist.HL;
	unsigned char temp=inc2(loadMEMB(regist.HL));

	writeMEMB(patata, temp);
}

// 0x35
void dec_hlm (unsigned int) {
	reconstruirHL();
	char16_t patata=regist.HL;
	unsigned char temp=dec2(loadMEMB(regist.HL));

	writeMEMB(patata, temp);
}

//LD (HL), d8, 0x36
void ld_hlld8(unsigned char valor){
	reconstruirHL();
	writeMEMB(regist.HL, valor);
}

//SCF, 0x37
void scf (unsigned int) {
	regist.F= regist.F | 0x10;//activar flag acarreo
	regist.F= regist.F & 0xDF; //desactivar half
	regist.F= regist.F & 0xBF; //desactivar N
}

//JR C,r8, 0x38
void jr_cr8( char valor){
	unsigned char u = regist.F >> 4;
	if(u== 0){
		machine_cycle+=8;
	}else{
		regist.PC+= (signed char) valor;
		
		machine_cycle=+12;
	}
}

//ADD HL,SP, 0x39
void add_hl_SP (unsigned int) {
	reconstruirHL();
	suma2(&regist.HL, regist.SP);
	deconstruirHL();
}

//LD A,(HL-), 0x3a
void ld_a_hlm (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.A = loadMEMB((regist.HL - 0x01));
}

// 0x3b
void dec_sp (unsigned int) { regist.SP=regist.SP - 0x01; }

// 0x3c
void inc_a (unsigned int) { inc(&regist.A); }

// 0x3d
void dec_a (unsigned int) { dec(&regist.A); }

//LD A,d8, 0x3e
void ld_a8(unsigned char valor){
	regist.A=valor;
}

//CCF 0x3f
void CCF (unsigned int) {
	unsigned char flagC= (regist.F >> 4) & 0x01;
	if(flagC == 1){
		regist.F= regist.F & 0xEF;
	}else{
		regist.F= regist.F | 0x10;
	}

	regist.F= regist.F & 0xDF; //desactivar half
	regist.F= regist.F & 0xBF; //desactivar N
}

//LD B, C  0x40, copia B a B
void ld_b_b (unsigned int) { 
	regist.B = regist.B;
	reconstruirBC();
	
}

//LD B, C  0x41, copia C a B
void ld_b_c (unsigned int) { 
	regist.B = regist.C;
	reconstruirBC();
}

//LD B, D  0x42, copia D a B
void ld_b_d (unsigned int) { 
	regist.B = regist.D;
	reconstruirBC();
}

//LD B, E  0x43, copia E a B
void ld_b_e (unsigned int) { 
	regist.B = regist.E;
	reconstruirBC();	
}

//LD B, H  0x44, copia H a B
void ld_b_h (unsigned int) { 
	regist.B = regist.H;
	reconstruirBC();	
}

//LD B, L  0x45, copia L a B
void ld_b_l (unsigned int) { 
	regist.B = regist.L;
	reconstruirBC();	
}

//LD B, HL  0x46, carga HL a B
void ld_b_hl (unsigned int) { 
	
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.B = loadMEMB(regist.HL);
	reconstruirBC();
	}

//LD B, A  0x47, copia A a B
void ld_b_a (unsigned int) { 
	regist.B = regist.A;
	reconstruirBC();
}

//LD C, B 0x48, copia B a C
void ld_c_b (unsigned int) {
	regist.C = regist.B;
	reconstruirBC();
}

//LD C, C 0x49, copia C a C
void ld_c_c (unsigned int) {
	regist.C = regist.C;
	reconstruirBC();
}

//LD C, D 0x4a, copia D a C
void ld_c_d (unsigned int) {
	regist.C = regist.D;
	reconstruirBC();
}

//LD C, e 0x4b, copia E a C
void ld_c_e (unsigned int) {
	regist.C = regist.E;
	reconstruirBC();
}

//LD C, B 0x4c, copia H a C
void ld_c_h (unsigned int) {
	regist.C = regist.H;
	reconstruirBC();
}

//LD C, B 0x4d, copia L a C
void ld_c_l (unsigned int) {
	regist.C = regist.L;
	reconstruirBC();
}

//LD C, HL  0x4e, carga HL a C
void ld_c_hl (unsigned int) { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.C = loadMEMB(regist.HL);
	reconstruirBC();
}

//LD C, A  0x4f, copia A a C
void ld_c_a (unsigned int) {
	regist.C = regist.A;
	reconstruirBC();
}

//LD D, B 0x50, copia B a D
void ld_d_b (unsigned int) {
	regist.D = regist.B;
	reconstruirDE();
}

//LD D, C 0x51, copia C a D
void ld_d_c (unsigned int) {
	regist.D = regist.C;
	reconstruirDE();
}

//LD D, D 0x52, copia D a D
void ld_d_d (unsigned int) {
	regist.D = regist.D;
	reconstruirDE();
}

//LD D, e 0x53, copia E a D
void ld_d_e (unsigned int) {
	regist.D = regist.E;
	reconstruirDE();
}

//LD D, B 0x54, copia H a D
void ld_d_h (unsigned int) {
	regist.D = regist.H;
	reconstruirDE();
}

//LD D, B 0x55, copia L a D
void ld_d_l (unsigned int) {
	regist.D = regist.L;
	reconstruirDE();
}

//LD D, HL  0x56, carga HL a D
void ld_d_hl (unsigned int) { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.D = loadMEMB(regist.HL);
	reconstruirDE();
	}

//LD E, A  0x57, copia A a E
void ld_d_a (unsigned int) {
	regist.D = regist.A;
	reconstruirDE();
}

//LD E, B 0x58, copia B a E
void ld_e_b (unsigned int) {
	regist.E = regist.B;
	reconstruirDE();
}

//LD E, C 0x59, copia C a E
void ld_e_c (unsigned int) {
	regist.E = regist.C;
	reconstruirDE();
}

//LD E, D 0x5a, copia D a E
void ld_e_d (unsigned int) {
	regist.E = regist.D;
	reconstruirDE();
}

//LD E, e 0x5b, copia E a E
void ld_e_e (unsigned int) {
	regist.E = regist.E;
	reconstruirDE();
}

//LD E, B 0x5c, copia H a E
void ld_e_h (unsigned int) {
	regist.E = regist.H;
	reconstruirDE();
}

//LD E, B 0x5d, copia L a E
void ld_e_l (unsigned int) {
	regist.E = regist.L;
	reconstruirDE();
}

//LD E, HL  0x5e, carga HL a E
void ld_e_hl (unsigned int) { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.E = loadMEMB(regist.HL);
	reconstruirDE();
}

//LD E, A  0x5f, copia A a E
void ld_e_a (unsigned int) {
	regist.E = regist.A;
	reconstruirDE();
}

//LD H, B 0x60, copia B a H
void ld_h_b (unsigned int) {
	regist.H = regist.B;
	reconstruirHL();
	}

//LD H, C 0x61, copia C a H
void ld_h_c (unsigned int) {
	regist.H = regist.C;
	reconstruirHL();
}

//LD H, D 0x62, copia D a H
void ld_h_d (unsigned int) {
	regist.H = regist.D;
	reconstruirHL();
}

//LD H, e 0x63, copia E a H
void ld_h_e (unsigned int) {
	regist.H = regist.E;
	reconstruirHL();
}

//LD H, B 0x64, copia H a H
void ld_h_h (unsigned int) {
	regist.H = regist.H;
	reconstruirHL();
}

//LD H, B 0x65, copia L a H
void ld_h_l (unsigned int) {
	regist.H = regist.L;
	reconstruirHL();
}

//LD H, HL  0x66, carga HL a H
void ld_h_hl (unsigned int) { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.H = loadMEMB(regist.HL);
	reconstruirHL();
	}

//LD H, A  0x67, copia A a H
void ld_h_a (unsigned int) {
	regist.H = regist.A;
	reconstruirHL();
}

//LD L, B 0x68, copia B a L
void ld_l_b (unsigned int) {
	regist.L = regist.B;
	reconstruirHL();
}

//LD L, C 0x69, copia C a L
void ld_l_c (unsigned int) {
	regist.L = regist.C;
	reconstruirHL();
}

//LD L, D 0x6a, copia D a L
void ld_l_d (unsigned int) {
	regist.L = regist.D;
	reconstruirHL();
}

//LD L, e 0x6b, copia E a L
void ld_l_e (unsigned int) {
	regist.L = regist.E;
	reconstruirHL();
}

//LD L, B 0x6c, copia H a L
void ld_l_h (unsigned int) {
	regist.L = regist.H;
	reconstruirHL();
}

//LD L, B 0x6d, copia L a L
void ld_l_l (unsigned int) {
	regist.L = regist.L;
	reconstruirHL();
}

//LD L, HL  0x6e, carga HL a L
void ld_l_hl (unsigned int) { 
	//hacer esto en la futura funcion loadMEM
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	//unsigned char16_t temp= regist.HL << 8;
	//unsigned char16_t temp2=0x0;
	//temp= temp | temp2; 
	
	regist.L = loadMEMB(regist.HL);
	reconstruirHL();
}

//LD L, A  0x6f, copia A a L
void ld_l_a (unsigned int) {
	regist.L = regist.A;
	reconstruirHL();
}

//LD (HL), B  0x70, guarda en mem B en la direccion de HL
void ld_hl_b (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.B);
}

//LD (HL), C  0x71, guarda en mem C en la direccion de HL
void ld_hl_c (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.C);
}

//LD (HL), D  0x72, guarda en mem D en la direccion de HL
void ld_hl_d (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.D);
}

//LD (HL), E  0x73, guarda en mem E en la direccion de HL
void ld_hl_e (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.E);
}

//LD (HL), H  0x74, guarda en mem H en la direccion de HL
void ld_hl_h (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.H);
}

//LD (HL), L  0x75, guarda en mem L en la direccion de HL
void ld_hl_l (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.L);
}


//HALT 0x76 Se para la CPU hasta que cualquier interrupcion llegue
void halt (unsigned int) {
	clock_cycle+=4;
	machine_cycle++;
	while(!interrrupt_enable){
		pause();

	}

}

//LD (HL), A  0x77, guarda en mem A en la direccion de HL
void ld_hl_a (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	writeMEMB(regist.HL, regist.A);
}

//LD A, B 0x78, copia B a A
void ld_a_b (unsigned int) {regist.A = regist.B;}

//LD A, C 0x79, copia C a A
void ld_a_c (unsigned int) {regist.A = regist.C;}

//LD A, D 0x7a, copia D a A
void ld_a_d (unsigned int) {regist.A = regist.D;}

//LD A, E 0x7b, copia E a A
void ld_a_e (unsigned int) {regist.A = regist.E;}

//LD A, B 0x7c, copia H a A
void ld_a_h (unsigned int) {regist.A = regist.H;}

//LD A, B 0x7d, copia L a A
void ld_a_l (unsigned int) {regist.A = regist.L;}

//LD A, HL  0x7e, carga HL a A
void ld_a_hl (unsigned int) { 
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
void ld_a_a (unsigned int) {regist.A = regist.A;}

//ADD A, B 0x80, Suma A y B y lo guarda en A
void add_a_b (unsigned int) {
	suma(&regist.A, regist.B);

}

//ADD A, C 0x81, Suma A y C y lo guarda en A
void add_a_c (unsigned int) {
	suma(&regist.A, regist.C);


}

//ADD A, D 0x82, Suma A y D y lo guarda en A
void add_a_d (unsigned int) {
	suma(&regist.A, regist.D);

}

//ADD A, E 0x83, Suma A y E y lo guarda en A
void add_a_e (unsigned int) {
	suma(&regist.A, regist.E);

}

//ADD A, H 0x84, Suma A y H y lo guarda en A
void add_a_h (unsigned int) {
	suma(&regist.A, regist.H);

}

//ADD A, L 0x85, Suma A y L y lo guarda en A
void add_a_l (unsigned int) {
	suma(&regist.A, regist.L);

}

//ADD A, HL 0x86, Suma A y (HL) y lo guarda en A
void add_a_hl (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	suma(&regist.A, temp);
}

//ADD A, A 0x87, Suma A y A y lo guarda en A
void add_a_a (unsigned int) {
	suma(&regist.A, regist.A);

}

//ADC A, B, 0x88 Suma A y B con acarreo, se guarda en A
void adc_a_b (unsigned int) {
	sumaC(&regist.A, regist.B);

}

//ADC A, C, 0x89 Suma A y C con acarreo, se guarda en A
void adc_a_c (unsigned int) {
	sumaC(&regist.A, regist.C);

}

//ADC A, D, 0x8a Suma A y D con acarreo, se guarda en A
void adc_a_d (unsigned int) {
	sumaC(&regist.A, regist.D);
;
}

//ADC A, E, 0x8b Suma A y E con acarreo, se guarda en A
void adc_a_e (unsigned int) {
	sumaC(&regist.A, regist.E);

}

//ADC A, H, 0x8c Suma A y H con acarreo, se guarda en A
void adc_a_h (unsigned int) {
	sumaC(&regist.A, regist.H);

}

//ADC A, L, 0x8d Suma A y L con acarreo, se guarda en A
void adc_a_l (unsigned int) {
	sumaC(&regist.A, regist.L);

}

//ADC A, (HL), 0x8e Suma A y (HL) con acarreo, se guarda en A
void adc_a_hl (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	sumaC(&regist.A, temp);
}

//ADC A, A, 0x8f Suma A y A con acarreo, se guarda en A
void adc_a_a (unsigned int) {
	sumaC(&regist.A, regist.A);

}

//SUB A, B 0x90, resta A y B y lo guarda en A
void sub_a_b (unsigned int) {
	resta(&regist.A, regist.B);

}

//SUB A, C 0x91, resta A y C y lo guarda en A
void sub_a_c (unsigned int) {
	resta(&regist.A, regist.C);

}

//SUB A, D 0x92, resta A y D y lo guarda en A
void sub_a_d (unsigned int) {
	resta(&regist.A, regist.D);

}

//SUB A, E 0x93, resta A y E y lo guarda en A
void sub_a_e (unsigned int) {
	resta(&regist.A, regist.E);

}

//SUB A, H 0x94, resta A y H y lo guarda en A
void sub_a_h (unsigned int) {
	resta(&regist.A, regist.H);

}

//SUB A, L 0x95, resta A y L y lo guarda en A
void sub_a_l (unsigned int) {
	resta(&regist.A, regist.L);

}

//SUB A, HL 0x96, resta A y (HL) y lo guarda en A
void sub_a_hl (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	resta(&regist.A, temp);
}

//SUB A, A 0x97, resta A y A y lo guarda en A
void sub_a_a (unsigned int) {
	resta(&regist.A, regist.A);

}



// 0x98
void sbc_a_b (unsigned int) {restaC(&regist.A, regist.B); }

// 0x99
void sbc_a_c (unsigned int) {restaC(&regist.A, regist.C); }

// 0x9a
void sbc_a_d (unsigned int) {restaC(&regist.A, regist.D); }

// 0x9b
void sbc_a_e (unsigned int) {restaC(&regist.A, regist.E); }

// 0x9c
void sbc_a_h (unsigned int) {restaC(&regist.A, regist.H); }

// 0x9d
void sbc_a_l (unsigned int) {restaC(&regist.A, regist.L); }

// 0x9e
void sbc_a_hl (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	restaC(&regist.A, temp);
}

// 0x9f
void sbc_a_a (unsigned int) {restaC(&regist.A, regist.A); }

// 0xa0
void and_b (unsigned int) {ando(&regist.B); }

// 0xa1
void and_c (unsigned int) {ando(&regist.C); }

// 0xa2
void and_d (unsigned int) {ando(&regist.D); }

// 0xa3
void and_e (unsigned int) {ando(&regist.E); }

// 0xa4
void and_h (unsigned int) {ando(&regist.H); }

// 0xa5
void and_l (unsigned int) {ando(&regist.L); }

// 0xa6
void and_hlp(unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L; 
	unsigned char temp= loadMEMB(regist.HL);
	ando(&temp);
}

// 0xa7
void and_a (unsigned int) {ando(&regist.A); }

// 0xa8
void xor_b (unsigned int) {xoro(&regist.B); }

// 0xa9
void xor_c (unsigned int) {xoro(&regist.C); }

// 0xaa
void xor_d (unsigned int) {xoro(&regist.D); }

// 0xab
void xor_e (unsigned int) {xoro(&regist.E); }

// 0xac
void xor_h (unsigned int) {xoro(&regist.H); }

// 0xad
void xor_l (unsigned int) {xoro(&regist.L); }

// 0xae
void xor_hlp (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L;
	unsigned char temp= loadMEMB(regist.HL);
	xoro(&temp);
}

// 0xaf
void xor_a (unsigned int) {xoro(&regist.A); }

// 0xb0
void or_b (unsigned int) {oro(&regist.B); }

// 0xb1
void or_c (unsigned int) {oro(&regist.C); }

// 0xb2
void or_d (unsigned int) {oro(&regist.D); }

// 0xb3
void or_e (unsigned int) {oro(&regist.E); }

// 0xb4
void or_h (unsigned int) {oro(&regist.H); }

// 0xb5
void or_l (unsigned int) {oro(&regist.L); }

// 0xb6
void or_hlp (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L; 
	unsigned char temp= loadMEMB(regist.HL);
	oro(&temp);
}

// 0xb7
void or_a (unsigned int) {oro(&regist.A); }

// 0xb8
void cp_b (unsigned int) {cp(regist.B); }

// 0xb9
void cp_c (unsigned int) {cp(regist.C); }

// 0xba
void cp_d (unsigned int) {cp(regist.D); }

// 0xbb
void cp_e (unsigned int) {cp(regist.E); }

// 0xbc
void cp_h (unsigned int) {cp(regist.H); }

// 0xbd
void cp_l (unsigned int) {cp(regist.L); }

// 0xbe
void cp_hlp (unsigned int) {
	regist.HL=regist.H;
	regist.HL=regist.HL<<8;
	regist.HL=regist.HL|regist.L; 
	unsigned char temp= loadMEMB(regist.HL);
	cp(temp);
}

// 0xbf
void cp_a (unsigned int) {cp(regist.A); }

// 0xc0
void ret_nz (unsigned int) {
	unsigned char u = regist.F >> 7;
	if(u == 1){
		machine_cycle+=8;
	}else{
		regist.PC= loadMEM16pila(&regist.SP);
		machine_cycle=+20;
	}
}

//0xc1 POP BC, dia 2 de noviembre de 2020, esto lleva un anyo planteado y tras un paron desde junio volvemos a la carga sin acordarme de la mitad de las cosas BRING BACK THE FURYO STYLE!
void pop_bc (unsigned int) {
	reconstruirBC();
	regist.BC= loadMEM16pila(&regist.SP);
	deconstruirBC();
}

//0xc2
void jp_nz_a16(unsigned short valor){ //creo que tambien hay que comprobar que el flag de carry este activado, pero patata, gran probabilidad de error en algun momento
	unsigned char u = regist.F >> 7;
	if(u==0){
		regist.PC=valor;
		clock_cycle+=16;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xc3
void jp_a16(unsigned short valor){
	regist.PC=valor;
}

//0xc4
void call_nz_a16(unsigned short valor){
	unsigned char u = regist.F >> 7;
	if(u==0){
		writeMEM16pila((char16_t) regist.PC,&regist.SP);
		regist.PC=valor;
		clock_cycle+=24;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xc5
void push_bc (unsigned int) {
	reconstruirBC();
	writeMEM16pila(regist.BC, &regist.SP);
	deconstruirBC();
}

//0xc6
void add_a_d8(unsigned char valor){
	suma(&regist.A, valor);
}

//0xc7
void rst_00h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0000;
}

//0xc8
void ret_z (unsigned int) {
	unsigned char u = regist.F >> 7;
	if(u==1){
		regist.PC = loadMEM16pila(&regist.SP);
		clock_cycle+=20;
	}else{
		clock_cycle+=8;
	}
}

//0xc9
void ret (unsigned int) {
	regist.PC= loadMEM16pila(&regist.SP);
}

//0xca
void jp_z_a16(unsigned short valor){
	unsigned char u = regist.F >> 7;
	if(u==1){
		regist.PC=valor;
		clock_cycle+=16;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xcb PREFIX CB, aqui, mira socio, ni puta idea, hay como otra 256 instrucciones dentro de esta, pendiente de investigar, continuo con las que se hacer

//0xcc
void call_z_a16(unsigned short valor){
	unsigned char u = regist.F >> 7;
	if(u==1){
		writeMEM16pila((char16_t) regist.PC,&regist.SP);
		regist.PC=valor;
		clock_cycle+=24;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xcd
void call_a16(unsigned short valor){
	writeMEM16pila((char16_t) regist.PC,&regist.SP);
	regist.PC=valor;
}

//0xce
void adc_a_d8(unsigned char valor){
	sumaC(&regist.A, valor);
}

//0xcf
void RST_08H (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0008;
}

//0xd0
void ret_nc (unsigned int) {
	unsigned char u = regist.F >> 4 & 0x01;
	if(u == 1){
		machine_cycle+=8;
	}else{
		regist.PC= loadMEM16pila(&regist.SP);
		machine_cycle=+20;
	}
}

//0xd1
void pop_de (unsigned int) {
	reconstruirDE();
	regist.DE= loadMEM16pila(&regist.SP);
	deconstruirDE();
}

//0xd2
void jp_nc_a16(unsigned short valor){
	unsigned char u = regist.F >> 4 & 0x01;
	if(u==0){
		regist.PC=valor;
		clock_cycle+=16;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xd4
void call_nc_a16(unsigned short valor){
	unsigned char u = regist.F >> 4 & 0x01;
	if(u==0){
		writeMEM16pila((char16_t) regist.PC,&regist.SP);
		regist.PC=valor;
		clock_cycle+=24;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xd5
void push_de (unsigned int) {
	reconstruirDE();
	writeMEM16pila(regist.DE, &regist.SP);
	deconstruirDE();
}

//0xd6
void sub_d8(unsigned char valor){
	resta(&regist.A, valor);
}

//0xd7
void rst_10h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0010;
}

//0xd8
void ret_c (unsigned int) {
	unsigned char u = regist.F >> 4 & 0x01;
	if(u==1){
		regist.PC = loadMEM16pila(&regist.SP);
		clock_cycle+=20;
	}else{
		clock_cycle+=8;
	}
}

//0xd9
void reti (unsigned int) {
	regist.PC= loadMEM16pila(&regist.SP);
	//habilitar interrupciones, pero todavia no estan hechas
}

//0xda
void jp_c_a16(unsigned short valor){
	unsigned char u = regist.F >> 4 & 0x01;
	if(u==1){
		regist.PC=valor;
		clock_cycle+=16;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xdc
void call_c_a16(unsigned short valor){
	unsigned char u = regist.F >> 4 & 0x01;
	if(u==1){
		writeMEM16pila((char16_t) regist.PC,&regist.SP);
		regist.PC=valor;
		clock_cycle+=24;//REVISAAAAAAAAR
	}else{
		clock_cycle+=12;
	}
}

//0xde
void sbc_a_d8(unsigned char valor){
	restaC(&regist.A, valor);
}

//0xdf
void rst_18h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0018;
}

//0xe0
void ldh_a8_a(unsigned char valor){
	writeMEMB(0xff00+valor, regist.A);
}

//0xe1
void pop_hl (unsigned int) {
	reconstruirHL();
	regist.HL= loadMEM16pila(&regist.SP);
	deconstruirHL();
}

//0xe2
void ld_ca (unsigned int) {
	writeMEMB(0xff00+regist.C, regist.A);
}

//0xe5
void push_hl (unsigned int) {
	reconstruirHL();
	writeMEM16pila(regist.HL, &regist.SP);
	deconstruirHL();
}

//0xe6
void and_d8(unsigned char valor){
	regist.A= regist.A & valor;

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

//0xe7
void rst_20h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0020;
}

//0xe8 Esta va a petar fuertemente, he copiado la suma de dos registros de 16 bits y tru;eado uno para que sea de 8 bits, seguro que los calculos no encajan, no he revisado flags ni nada en el manual
void add_sp_r8(char valor){
	char32_t carry= regist.SP + valor;

	//para comprobar el half
	char16_t half1=regist.SP & 0xFF;
	char16_t half2=valor & 0xF;
	char16_t half3=half1 + half2;

	regist.SP=(char16_t) (carry & 0xFFFF);

	if((carry >> 16) > 0x01){
		regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	//MUY POTENTE FALLO AQUI
	if((half3>>8) >=0x01){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}
	
	regist.F= regist.F & 0x7F; //desactivar el flag Z
	regist.F= regist.F &  0xBF; //desactivar el flag N
}

//0xe9
void jp_hl (unsigned int) {
	reconstruirHL();
	regist.PC= regist.HL;
}

//0xea
void ld_a16_a(unsigned short valor){
	writeMEMB((char16_t) valor, regist.A);
}

//0xee
void xor_d8(unsigned char valor){
	xoro(&valor);
}

//0xef
void rst_28h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0028;
}

//0xf0
void ldh_a_a8(unsigned char valor){
	regist.A= loadMEMB(0xff00+valor);
}

//0xf1
void pop_af (unsigned int) {
	regist.AF=regist.A;
	regist.AF=regist.AF<<8;
	regist.AF=regist.AF|regist.F;
	regist.AF= loadMEM16pila(&regist.SP);
	regist.A=(unsigned char) ((regist.AF >>8) & 0xFF);
	regist.F=(unsigned char) (regist.AF & 0xFF);
}

//0xf2
void la_ac (unsigned int) {
	regist.A= loadMEMB(0xff00 + regist.C);
}

//0xf3 deshabilita las interrupciones despues de ejecutar esta instrunccion
void di (unsigned int) {
	interrrupt_enable=0;
}

//0xf5
void push_af (unsigned int) {
	regist.AF=regist.A;
	regist.AF=regist.AF<<8;
	regist.AF=regist.AF|regist.F;
	writeMEM16pila(regist.AF, &regist.SP);
}

//0xf6
void or_d8(unsigned char valor){
	regist.A= regist.A | valor;

	if(regist.A==0){
		regist.F= regist.F | 0x80;
	}
	else{
		regist.F= regist.F & 0x7F;
	}
	
	regist.F= regist.F & 0xBF;//pone el flag de restar a 0;
	regist.F= regist.F & 0xEF;// flag carry
	regist.F= regist.F & 0xDF;//desactiva el half
}

//0xf7
void rst_30h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0030;
}

//0xf8 potencial errores varios, checkear flags y operaciones, mismo motivo que en la add de mas arriba
void ld_hl_spr8(char valor){
	int carry = regist.SP + valor;

	//para comprobar el half
	unsigned short half1=regist.SP & 0xFF;
	unsigned short half2=valor & 0xF;
	unsigned short half3=half1 + half2;

	regist.HL=(char16_t) (carry & 0xFFFF);

	if((carry >> 16) > 0x01){
		regist.F= regist.F | 0x10;
	}else{
		regist.F= regist.F & 0xEF;//desactivar carry
	}

	//MUY POTENTE FALLO AQUI
	if((half3>>8) >=0x01){ //comprobar half
		regist.F= regist.F | 0x20;
	}else{
		regist.F= regist.F & 0xDF;
	}

	regist.F= regist.F & 0x7F; //desactivar el flag Z
	regist.F= regist.F &  0xBF; //desactivar el flag N
}

//0xf9
void ld_sp_hl (unsigned int) {
	regist.SP= regist.HL;
}

//0xfa
void ld_a_a16(unsigned short valor){
	regist.A= loadMEMB((char16_t) valor);
}

//0xfb habilita interrupciones depues de ejecutar la instruccion
void ei (unsigned int) {
	interrrupt_enable=1;
}

//0xfe revisar que no he mirado la documentacion
void cp_d8(unsigned char valor){
	cp(valor);
}

//0xff
void rst_38h (unsigned int) {
	writeMEM16pila((char16_t) regist.PC, &regist.SP);
	regist.PC=0x0038;
}

void nada (unsigned int) {

}



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
	//inc_b();
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
	//instructions[0x81].action();
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
	string exit;
	unsigned char ojo=0xf;
	int prueba=0;
	int instt;
	int parametro;
	while(1){
		//cin>>exit;
		cin>> hex >> instt;
		cout<<"has puesto: "<<instt<<"\n";
		/*if(instructions[instt].action_bit_number==0){
			instructions[instt].action(prueba);
		}else{
			cin>> hex >> parametro;
			instructions[instt].action_parameter=parametro;
			instructions[instt].action(instructions[instt].action_parameter);
		}*/
		
		if(instructions[instt].action_bit_number!=0){
			cin>> hex >> parametro;
			instructions[instt].action_parameter=parametro;
		}
		instructions[instt].action(instructions[instt].action_parameter);

		//ld_b8(ojo);
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
	}
	

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


