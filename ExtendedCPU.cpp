#include <bits/stdc++.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "registro.h"
#include "memoria.h"
#include "ExtendedCPU.h"
#include "cpu.h"
using namespace std;

//aqui vienen las instrucciones CB
const struct CBinstruction CBinstructions[256]={
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_b },//0x00 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_c },//0x01
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_d },//0x02
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_e },//0x03
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_h },//0x04
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_l },//0x05
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:rlc_hl },//0x06
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rlc_a },//0x07
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_b },//0x08 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_c },//0x09
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_d },//0x0a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_e },//0x0b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_h },//0x0c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_l },//0x0d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:rrc_hl },//0x0e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rrc_a },//0x0f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_b },//0x10 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_c },//0x11
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_d },//0x12
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_e },//0x13
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_h },//0x14
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_l },//0x15
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:rl_hl },//0x16
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rl_a },//0x17
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_b },//0x18 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_c },//0x19
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_d },//0x1a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_e },//0x1b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_h },//0x1c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_l },//0x1d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:rr_hl },//0x1e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:rr_a },//0x1f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_b },//0x20 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_c },//0x21
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_d },//0x22
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_e },//0x23
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_h },//0x24
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sla_l },//0x25
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:sla_hl },//0x26
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_a },//0x27
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_b },//0x28 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_c },//0x29
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_d },//0x2a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_e },//0x2b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_h },//0x2c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_l },//0x2d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:sra_hl },//0x2e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:sra_a },//0x2f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_b },//0x30 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_c },//0x31
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_d },//0x32
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_e },//0x33
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_h },//0x34
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_l },//0x35
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:swap_hl },//0x36
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:swap_a },//0x37
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_b },//0x38 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_c },//0x39
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_d },//0x3a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_e },//0x3b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_h },//0x3c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_l },//0x3d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:srl_hl },//0x3e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:srl_a },//0x3f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_b },//0x40 
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_c },//0x41
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_d },//0x42
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_e },//0x43
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_h },//0x44
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_l },//0x45
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_0_hl },//0x46
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_0_a },//0x47
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_b },//0x48
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_c },//0x49
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_d },//0x4a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_e },//0x4b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_h },//0x4c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_l },//0x4d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_1_hl },//0x4e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_1_a },//0x4f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_b },//0x50
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_c },//0x51
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_d },//0x52
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_e },//0x53
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_h },//0x54
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_l },//0x55
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_2_hl },//0x56
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_2_a },//0x57
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_b },//0x58
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_c },//0x59
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_d },//0x5a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_e },//0x5b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_h },//0x5c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_l },//0x5d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_3_hl },//0x5e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_3_a },//0x5f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_b },//0x60
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_c },//0x61
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_d },//0x62
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_e },//0x63
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_h },//0x64
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_l },//0x65
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_4_hl },//0x66
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_4_a },//0x67
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_b },//0x68
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_c },//0x69
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_d },//0x6a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_e },//0x6b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_h },//0x6c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_l },//0x6d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_5_hl },//0x6e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_5_a },//0x6f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_b },//0x70
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_c },//0x71
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_d },//0x72
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_e },//0x73
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_h },//0x74
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_l },//0x75
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_6_hl },//0x76
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_6_a },//0x77
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_b },//0x78
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_c },//0x79
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_d },//0x7a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_e },//0x7b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_h },//0x7c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_l },//0x7d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:bit_7_hl },//0x7e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:bit_7_a },//0x7f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_b },//0x80
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_c },//0x81
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_d },//0x82
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_e },//0x83
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_h },//0x84
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_l },//0x85
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_0_hl },//0x86
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_0_a },//0x87
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_b },//0x88
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_c },//0x89
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_d },//0x8a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_e },//0x8b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_h },//0x8c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_l },//0x8d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_1_hl },//0x8e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_1_a },//0x8f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_b },//0x90
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_c },//0x91
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_d },//0x92
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_e },//0x93
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_h },//0x94
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_l },//0x95
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_2_hl },//0x96
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_2_a },//0x97
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_b },//0x98
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_c },//0x99
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_d },//0x9a
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_e },//0x9b
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_h },//0x9c
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_l },//0x9d
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_3_hl },//0x9e
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_3_a },//0x9f
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_b },//0xa0
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_c },//0xa1
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_d },//0xa2
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_e },//0xa3
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_h },//0xa4
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_l },//0xa5
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_4_hl },//0xa6
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_4_a },//0xa7
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_b },//0xa8
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_c },//0xa9
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_d },//0xaa
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_e },//0xab
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_h },//0xac
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_l },//0xad
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_5_hl },//0xae
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_5_a },//0xaf
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_b },//0xb0
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_c },//0xb1
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_d },//0xb2
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_e },//0xb3
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_h },//0xb4
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_l },//0xb5
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_6_hl },//0xb6
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_6_a },//0xb7
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_b },//0xb8
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_c },//0xb9
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_d },//0xba
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_e },//0xbb
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_h },//0xbc
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_l },//0xbd
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:res_7_hl },//0xbe
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:res_7_a },//0xbf
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_b },//0xc0
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_c },//0xc1
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_d },//0xc2
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_e },//0xc3
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_h },//0xc4
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_l },//0xc5
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_0_hl },//0xc6
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_0_a },//0xc7
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_b },//0xc8
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_c },//0xc9
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_d },//0xca
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_e },//0xcb
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_h },//0xcc
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_l },//0xcd
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_1_hl },//0xce
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_1_a },//0xcf
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_b },//0xd0
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_c },//0xd1
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_d },//0xd2
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_e },//0xd3
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_h },//0xd4
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_l },//0xd5
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_2_hl },//0xd6
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_2_a },//0xd7
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_b },//0xd8
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_c },//0xd9
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_d },//0xda
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_e },//0xdb
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_h },//0xdc
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_l },//0xdd
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_3_hl },//0xde
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_3_a },//0xdf
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_b },//0xe0
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_c },//0xe1
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_d },//0xe2
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_e },//0xe3
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_h },//0xe4
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_l },//0xe5
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_4_hl },//0xe6
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_4_a },//0xe7
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_b },//0xe8
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_c },//0xe9
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_d },//0xea
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_e },//0xeb
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_h },//0xec
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_l },//0xed
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_5_hl },//0xee
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_5_a },//0xef
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_b },//0xf0
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_c },//0xf1
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_d },//0xf2
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_e },//0xf3
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_h },//0xf4
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_l },//0xf5
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_6_hl },//0xf6
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_6_a },//0xf7
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_b },//0xf8
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_c },//0xf9
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_d },//0xfa
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_e },//0xfb
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_h },//0xfc
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_l },//0xfd
	{ valid_instruction:true, clock_cycle:16, machine_cycle:4, action:set_7_hl },//0xfe
	{ valid_instruction:true, clock_cycle:8, machine_cycle:2, action:set_7_a }//0xff
	
	};


static unsigned char rlc(unsigned char registro){
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


static unsigned char rrc(unsigned char registro){
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

static unsigned char rl(unsigned char registro){
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

static unsigned char rr(unsigned char registro){
	//cogemos el valor del bit de carry
	/*unsigned char bit=regist.F & 0x10;
	bit= bit <<3;
	bit= bit & 0x80;// para poder sumar el bit, que sera 0 o 1, como vaya la cosa
	unsigned char C= (regist.F >>4) & 0x01;
	//coges el bit menos significativo y lo dejas a la derecha, asi sirve para evaluar si se activa el flag y ademas se mete al final como buena rotacion que es
	unsigned char u = registro & 0x01;
	
	if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}

	//registro = registro >> 1;

	//como es una rotacion, se le mete al final lo que "salio"
	registro >>=1;

	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }
	
    return registro;*/
	//(regist.F >>4) & 0x01
	unsigned char bit=registro & 0x01;
	registro >>= 1;
	if((regist.F >>4) & 0x01) registro |= 0x80;
	
	if(bit & 0x01){
		regist.F = regist.F | 0x10;
	}
	else{
		regist.F= regist.F & 0xEF;
	}
	
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }
	
	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	
	return registro;

}

static unsigned char sla(unsigned char registro){
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

static unsigned char sra(unsigned char registro){
    unsigned char u= registro & 0x01;
	unsigned char bitquesaleyvuelve;
    if (u != 0){
		regist.F = regist.F | 0x10;
		bitquesaleyvuelve= 0x80;
	}else
	{
		regist.F= regist.F & 0xEF;
		bitquesaleyvuelve= 0x00;
	}
    registro=registro >> 1;
	registro= registro + bitquesaleyvuelve;


    regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
    
}

static unsigned char swap(unsigned char registro){
	unsigned char parte_baja=(registro & 0xF0)>> 4;
	unsigned char parte_alta=(registro & 0x0F)<< 4;
	registro= parte_baja | parte_alta;
	
	regist.F= regist.F & 0xEF;//desactiva carry
	regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
}

static unsigned char srl(unsigned char registro){
    unsigned char u= registro & 0x01;
    if (u != 0){
		regist.F = regist.F | 0x10;
	}else
	{
		regist.F= regist.F & 0xEF;
	}
    registro=registro >> 1;

    regist.F= regist.F & 0xDF;//desactiva el half
	regist.F= regist.F & 0xBF;//desactiva el flag N
	if(registro==0){
        regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }

    return registro;
    
}

static void bit(unsigned char bit, unsigned char registro){
	unsigned char u;
	if(bit==0x00){
		u=registro & 0x01;
	}else if(bit==0x01){
		u=registro & 0x02;
		u= u>>1;
	}else if(bit==0x02){
		u=registro & 0x04;
		u= u>>2;
	}else if(bit==0x03){
		u=registro & 0x08;
		u= u>>3;
	}else if(bit==0x04){
		u=registro & 0x10;
		u= u>>4;
	}else if(bit==0x05){
		u=registro & 0x20;
		u= u>>5;
	}else if(bit==0x06){
		u=registro & 0x40;
		u= u>>6;
	}else if(bit==0x07){
		u=registro & 0x80;
		u= u>>7;
	}
	if(u==0){
		regist.F = regist.F | 0x80;
    }else{
        regist.F= regist.F & 0x7F;//desactiva el flag 0
    }
	regist.F= regist.F & 0xBF;//desactiva el flag N
	regist.F= regist.F | 0x20;//activa el flag H

}

//0x00 RLC B
void rlc_b(void){
	regist.B=rlc(regist.B);
	reconstruirBC();
}

//0x01 RLC C
void rlc_c(void){
	regist.C=rlc(regist.C);
	reconstruirBC();
}

//0x02 RLC D
void rlc_d(void){
	regist.D=rlc(regist.D);
	reconstruirDE();
}

//0x03 RLC E
void rlc_e(void){
	regist.E=rlc(regist.E);
	reconstruirDE();
}

//0x04 RLC H
void rlc_h(void){
	regist.H=rlc(regist.H);
	deconstruirHL();
}

//0x05 RLC L
void rlc_l(void){
	regist.L=rlc(regist.L);
	deconstruirHL();
}

//0x06 RLC (HL)
void rlc_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rlc(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x07 RLC A
void rlc_a(void){
	regist.A=rlc(regist.A);
	reconstruirAF();
}

//0x08 RRC B
void rrc_b(void){
	regist.B=rrc(regist.B);
	reconstruirBC();
}

//0x09 RRC C
void rrc_c(void){
	regist.C=rrc(regist.C);
	reconstruirBC();
}

//0x0a RRC D
void rrc_d(void){
	regist.D=rrc(regist.D);
	reconstruirDE();
}

//0x0b RRC E
void rrc_e(void){
	regist.E=rrc(regist.E);
	reconstruirDE();
}

//0x0c RRC H
void rrc_h(void){
	regist.H=rrc(regist.H);
	deconstruirHL();
}

//0x0d RRC L
void rrc_l(void){
	regist.L=rrc(regist.L);
	deconstruirHL();
}

//0x0e RRC (HL)
void rrc_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rrc(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x0f RRC A
void rrc_a(void){
	regist.A=rrc(regist.A);
	reconstruirAF();
}

//0x10 RL B
void rl_b(void){
	regist.B=rl(regist.B);
	reconstruirBC();
}

//0x11 RL C
void rl_c(void){
	regist.C=rl(regist.C);
	reconstruirBC();
}

//0x12 RL D
void rl_d(void){
	regist.D=rl(regist.D);
	reconstruirDE();
}

//0x13 RL E
void rl_e(void){
	regist.E=rl(regist.E);
	reconstruirDE();
}

//0x14 RL H
void rl_h(void){
	regist.H=rl(regist.H);
	deconstruirHL();
}

//0x15 RL L 
void rl_l(void){
	regist.L=rl(regist.L);
	deconstruirHL();
}

//0x16 RL (HL)
void rl_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rl(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x17 RL A 
void rl_a(void){
	regist.A=rl(regist.A);
	reconstruirAF();
}

//0x18 RR B 
void rr_b(void){
	regist.B=rr(regist.B);
	reconstruirBC();
}

//0x19 RR C 
void rr_c(void){
	regist.C=rr(regist.C);
	reconstruirBC();
}

//0x1a RR D 
void rr_d(void){
	regist.D=rr(regist.D);
	reconstruirDE();
}

//0x1b RR E 
void rr_e(void){
	regist.E=rr(regist.E);
	reconstruirDE();
}

//0x1c RR H 
void rr_h(void){
	regist.H=rl(regist.H);
	deconstruirHL();
}

//0x1d RR L 
void rr_l(void){
	regist.L=rl(regist.L);
	deconstruirHL();
}

//0x1e RR (HL)
void rr_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=rr(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x1f RR A 
void rr_a(void){
	regist.A=rr(regist.A);
	reconstruirAF();
}

//0x20 SLA B 
void sla_b(void){
	regist.B=sla(regist.B);
	reconstruirBC();
}

//0x21 SLA C 
void sla_c(void){
	regist.C=sla(regist.C);
	reconstruirBC();
}

//0x22 SLA D 
void sla_d(void){
	regist.D=sla(regist.D);
	reconstruirDE();
}

//0x23 SLA E 
void sla_e(void){
	regist.E=sla(regist.E);
	reconstruirDE();
}

//0x24 SLA H 
void sla_h(void){
	regist.H=sla(regist.H);
	reconstruirHL();
}

//0x25 SLA L 
void sla_l(void){
	regist.L=sla(regist.L);
	reconstruirHL();
}

//0x26 SLA (HL)
void sla_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=sla(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x27 SLA A 
void sla_a(void){
	regist.A=sla(regist.A);
	reconstruirAF();
}

//0x28 SRA B 
void sra_b(void){
	regist.B=sra(regist.B);
	reconstruirBC();
}

//0x29 SRA C 
void sra_c(void){
	regist.C=sra(regist.C);
	reconstruirBC();
}

//0x2a SRA D 
void sra_d(void){
	regist.D=sra(regist.D);
	reconstruirDE();
}

//0x2b SRA E 
void sra_e(void){
	regist.E=sra(regist.E);
	reconstruirDE();
}

//0x2c SRA H 
void sra_h(void){
	regist.H=sra(regist.H);
	reconstruirHL();
}

//0x2d SRA L 
void sra_l(void){
	regist.L=sra(regist.L);
	reconstruirHL();
}

//0x2e SRA (HL)
void sra_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=sra(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x2f SRA A 
void sra_a(void){
	regist.A=sra(regist.A);
	reconstruirAF();
}

//0x30 SWAP B 
void swap_b(void){
	regist.B=swap(regist.B);
	reconstruirBC();
}

//0x31 SWAP C 
void swap_c(void){
	regist.C=swap(regist.C);
	reconstruirBC();
}

//0x32 SWAP D 
void swap_d(void){
	regist.D=swap(regist.D);
	reconstruirDE();
}

//0x33 SWAP E 
void swap_e(void){
	regist.E=swap(regist.E);
	reconstruirDE();
}

//0x34 SWAP H 
void swap_h(void){
	regist.H=swap(regist.H);
	reconstruirHL();
}

//0x35 SWAP L 
void swap_l(void){
	regist.L=swap(regist.L);
	reconstruirHL();
}

//0x36 SWAP (HL)
void swap_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=swap(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x37 SWAP A 
void swap_a(void){
	regist.A=swap(regist.A);
	reconstruirAF();
}

//0x38 SRL B 
void srl_b(void){
	regist.B=srl(regist.B);
	reconstruirBC();
}

//0x39 SRL C 
void srl_c(void){
	regist.C=srl(regist.C);
	reconstruirBC();
}

//0x3a SRL D 
void srl_d(void){
	regist.D=srl(regist.D);
	reconstruirDE();
}

//0x3b SRL E 
void srl_e(void){
	regist.E=srl(regist.E);
	reconstruirDE();
}

//0x3c SRL H 
void srl_h(void){
	regist.H=srl(regist.H);
	reconstruirHL();
}

//0x3d SRL L 
void srl_l(void){
	regist.L=srl(regist.L);
	reconstruirHL();
}

//0x3e SRL (HL)
void srl_hl(void){
	reconstruirHL();
	unsigned char bytememrotado=srl(loadMEMB(regist.HL));
	writeMEMB(regist.HL, bytememrotado);
}

//0x3f SRL A 
void srl_a(void){
	regist.A=srl(regist.A);
	reconstruirAF();
}

//0x40 BIT 0,B
void bit_0_b(void){
	bit(0x00,regist.B);
}

//0x41 BIT 0,C
void bit_0_c(void){
	bit(0x00,regist.C);
}

//0x42 BIT 0,D
void bit_0_d(void){
	bit(0x00,regist.D);
}

//0x43 BIT 0,E
void bit_0_e(void){
	bit(0x00,regist.E);
}

//0x44 BIT 0,H
void bit_0_h(void){
	bit(0x00,regist.H);
}

//0x45 BIT 0,L
void bit_0_l(void){
	bit(0x00,regist.L);
}

//0x46 BIT 0,(HL)
void bit_0_hl(void){
	reconstruirHL();
	bit(0x00,loadMEMB(regist.HL));
}

//0x47 BIT 0,A
void bit_0_a(void){
	bit(0x00,regist.A);
}

//0x48 BIT 1,B
void bit_1_b(void){
	bit(0x01,regist.B);
}

//0x49 BIT 1,C
void bit_1_c(void){
	bit(0x01,regist.C);
}

//0x4a BIT 1,D
void bit_1_d(void){
	bit(0x01,regist.D);
}

//0x4b BIT 1,E
void bit_1_e(void){
	bit(0x01,regist.E);
}

//0x4c BIT 1,H
void bit_1_h(void){
	bit(0x01,regist.H);
}

//0x4d BIT 1,L
void bit_1_l(void){
	bit(0x01,regist.L);
}

//0x4e BIT 1,(HL)
void bit_1_hl(void){
	reconstruirHL();
	bit(0x01,loadMEMB(regist.HL));
}

//0x4f BIT 1,A
void bit_1_a(void){
	bit(0x01,regist.A);
}

//0x50 BIT 2,B
void bit_2_b(void){
	bit(0x02,regist.B);
}

//0x51 BIT 2,C
void bit_2_c(void){
	bit(0x02,regist.C);
}

//0x52 BIT 2,D
void bit_2_d(void){
	bit(0x02,regist.D);
}

//0x53 BIT 2,E
void bit_2_e(void){
	bit(0x02,regist.E);
}

//0x54 BIT 2,H
void bit_2_h(void){
	bit(0x02,regist.H);
}

//0x55 BIT 2,L
void bit_2_l(void){
	bit(0x02,regist.L);
}

//0x56 BIT 2,(HL)
void bit_2_hl(void){
	reconstruirHL();
	bit(0x02,loadMEMB(regist.HL));
}

//0x57 BIT 2,A
void bit_2_a(void){
	bit(0x02,regist.A);
}

//0x58 BIT 3,B
void bit_3_b(void){
	bit(0x03,regist.B);
}

//0x59 BIT 3,C
void bit_3_c(void){
	bit(0x03,regist.C);
}

//0x5a BIT 3,D
void bit_3_d(void){
	bit(0x03,regist.D);
}

//0x5b BIT 3,E
void bit_3_e(void){
	bit(0x03,regist.E);
}

//0x5c BIT 3,H
void bit_3_h(void){
	bit(0x03,regist.H);
}

//0x5d BIT 3,L
void bit_3_l(void){
	bit(0x03,regist.L);
}

//0x5e BIT 3,(HL)
void bit_3_hl(void){
	reconstruirHL();
	bit(0x03,loadMEMB(regist.HL));
}

//0x5f BIT 3,A
void bit_3_a(void){
	bit(0x03,regist.A);
}

//0x60 BIT 4,B
void bit_4_b(void){
	bit(0x04,regist.B);
}

//0x61 BIT 4,C
void bit_4_c(void){
	bit(0x04,regist.C);
}

//0x62 BIT 4,D
void bit_4_d(void){
	bit(0x04,regist.D);
}

//0x63 BIT 4,E
void bit_4_e(void){
	bit(0x04,regist.E);
}

//0x64 BIT 4,H
void bit_4_h(void){
	bit(0x04,regist.H);
}

//0x65 BIT 4,L
void bit_4_l(void){
	bit(0x04,regist.L);
}

//0x66 BIT 4,(HL)
void bit_4_hl(void){
	reconstruirHL();
	bit(0x04,loadMEMB(regist.HL));
}

//0x67 BIT 4,A
void bit_4_a(void){
	bit(0x04,regist.A);
}

//0x68 BIT 5,B
void bit_5_b(void){
	bit(0x05,regist.B);
}

//0x69 BIT 5,C
void bit_5_c(void){
	bit(0x05,regist.C);
}

//0x6a BIT 5,D
void bit_5_d(void){
	bit(0x05,regist.D);
}

//0x6b BIT 5,E
void bit_5_e(void){
	bit(0x05,regist.E);
}

//0x6c BIT 5,H
void bit_5_h(void){
	bit(0x05,regist.H);
}

//0x6d BIT 5,L
void bit_5_l(void){
	bit(0x05,regist.L);
}

//0x6e BIT 5,(HL)
void bit_5_hl(void){
	reconstruirHL();
	bit(0x05,loadMEMB(regist.HL));
}

//0x6f BIT 5,A
void bit_5_a(void){
	bit(0x05,regist.A);
}

//0x70 BIT 6,B
void bit_6_b(void){
	bit(0x06,regist.B);
}

//0x71 BIT 6,C
void bit_6_c(void){
	bit(0x06,regist.C);
}

//0x72 BIT 6,D
void bit_6_d(void){
	bit(0x06,regist.D);
}

//0x73 BIT 6,E
void bit_6_e(void){
	bit(0x06,regist.E);
}

//0x74 BIT 6,H
void bit_6_h(void){
	bit(0x06,regist.H);
}

//0x75 BIT 6,L
void bit_6_l(void){
	bit(0x06,regist.L);
}

//0x76 BIT 6,(HL)
void bit_6_hl(void){
	reconstruirHL();
	bit(0x06,loadMEMB(regist.HL));
}

//0x77 BIT 6,A
void bit_6_a(void){
	bit(0x06,regist.A);
}

//0x78 BIT 7,B
void bit_7_b(void){
	bit(0x07,regist.B);
}

//0x79 BIT 7,C
void bit_7_c(void){
	bit(0x07,regist.C);
}

//0x7a BIT 7,D
void bit_7_d(void){
	bit(0x07,regist.D);
}

//0x7b BIT 7,E
void bit_7_e(void){
	bit(0x07,regist.E);
}

//0x7c BIT 7,H
void bit_7_h(void){
	bit(0x07,regist.H);
}

//0x7d BIT 7,L
void bit_7_l(void){
	bit(0x07,regist.L);
}

//0x7e BIT 7,(HL)
void bit_7_hl(void){
	reconstruirHL();
	bit(0x07,loadMEMB(regist.HL));
}

//0x7f BIT 7,A
void bit_7_a(void){
	bit(0x07,regist.A);
}

//0x80 RES 0,B
void res_0_b(void){
	regist.B=regist.B & 0xFE;
	reconstruirBC();
}

//0x81 RES 0,C
void res_0_c(void){
	regist.C=regist.C & 0xFE;
	reconstruirBC();
}

//0x82 RES 0,D
void res_0_d(void){
	regist.D=regist.D & 0xFE;
	reconstruirDE();
}

//0x83 RES 0,E
void res_0_e(void){
	regist.E=regist.E & 0xFE;
	reconstruirDE();
}

//0x84 RES 0,H
void res_0_h(void){
	regist.H=regist.H & 0xFE;
	reconstruirHL();
}

//0x85 RES 0,L
void res_0_l(void){
	regist.L=regist.L & 0xFE;
	reconstruirHL();
}

//0x86 RES 0,(HL)
void res_0_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xFE);
	writeMEMB(regist.HL, ByteMEM);
}

//0x87 RES 0,A
void res_0_a(void){
	regist.A=regist.A & 0xFE;
}

//0x88 RES 1,B
void res_1_b(void){
	regist.B=regist.B & 0xFD;
	reconstruirBC();
}

//0x89 RES 1,C
void res_1_c(void){
	regist.C=regist.C & 0xFD;
	reconstruirBC();
}

//0x8a RES 1,D
void res_1_d(void){
	regist.D=regist.D & 0xFD;
	reconstruirDE();
}

//0x8b RES 1,E
void res_1_e(void){
	regist.E=regist.E & 0xFD;
	reconstruirDE();
}

//0x8c RES 1,H
void res_1_h(void){
	regist.H=regist.H & 0xFD;
	deconstruirHL();
}

//0x8d RES 1,L
void res_1_l(void){
	regist.L=regist.L & 0xFD;
	deconstruirHL();
}

//0x8e RES 1,(HL)
void res_1_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xFD);
	writeMEMB(regist.HL, ByteMEM);
}

//0x8f RES 1,A
void res_1_a(void){
	regist.A=regist.A & 0xFD;
}

//0x90 RES 2,B
void res_2_b(void){
	regist.B=regist.B & 0xFB;
	reconstruirBC();
}

//0x91 RES 2,C
void res_2_c(void){
	regist.C=regist.C & 0xFB;
	reconstruirBC();
}

//0x92 RES 2,D
void res_2_d(void){
	regist.D=regist.D & 0xFB;
	reconstruirDE();
}

//0x93 RES 2,E
void res_2_e(void){
	regist.E=regist.E & 0xFB;
	reconstruirDE();
}

//0x94 RES 2,H
void res_2_h(void){
	regist.H=regist.H & 0xFB;
	reconstruirHL();
}

//0x95 RES 2,L
void res_2_l(void){
	regist.L=regist.L & 0xFB;
	reconstruirHL();
}

//0x96 RES 2,(HL)
void res_2_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xFB);
	writeMEMB(regist.HL, ByteMEM);
}

//0x97 RES 2,A
void res_2_a(void){
	regist.A=regist.A & 0xFB;
}

//0x98 RES 3,B
void res_3_b(void){
	regist.B=regist.B & 0xF7;
	reconstruirBC();
}

//0x99 RES 3,C
void res_3_c(void){
	regist.C=regist.C & 0xF7;
	reconstruirBC();
}

//0x9a RES 3,D
void res_3_d(void){
	regist.D=regist.D & 0xF7;
	reconstruirDE();
}

//0x9b RES 3,E
void res_3_e(void){
	regist.E=regist.E & 0xF7;
	reconstruirDE();
}

//0x9c RES 3,H
void res_3_h(void){
	regist.H=regist.H & 0xF7;
	reconstruirHL();
}

//0x9d RES 3,L
void res_3_l(void){
	regist.L=regist.L & 0xF7;
	reconstruirHL();
}

//0x9e RES 3,(HL)
void res_3_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xF7);
	writeMEMB(regist.HL, ByteMEM);
}

//0x9f RES 3,A
void res_3_a(void){
	regist.A=regist.A & 0xF7;
}

//0xa0 RES 4,B
void res_4_b(void){
	regist.B=regist.B & 0xEF;
	reconstruirBC();
}

//0xa1 RES 4,C
void res_4_c(void){
	regist.C=regist.C & 0xEF;
	reconstruirBC();
}

//0xa2 RES 4,D
void res_4_d(void){
	regist.D=regist.D & 0xEF;
	reconstruirDE();
}

//0xa3 RES 4,E
void res_4_e(void){
	regist.E=regist.E & 0xEF;
	reconstruirDE();
}

//0xa4 RES 4,H
void res_4_h(void){
	regist.H=regist.H & 0xEF;
	reconstruirHL();
}

//0xa5 RES 4,L
void res_4_l(void){
	regist.L=regist.L & 0xEF;
	reconstruirHL();
}

//0xa6 RES 4,(HL)
void res_4_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xEF);
	writeMEMB(regist.HL, ByteMEM);
}

//0xa7 RES 4,A
void res_4_a(void){
	regist.A=regist.A & 0xEF;
}

//0xa8 RES 5,B
void res_5_b(void){
	regist.B=regist.B & 0xDF;
	reconstruirBC();
}

//0xa9 RES 5,C
void res_5_c(void){
	regist.C=regist.C & 0xDF;
	reconstruirBC();
}

//0xaa RES 5,D
void res_5_d(void){
	regist.D=regist.D & 0xDF;
	reconstruirDE();
}

//0xab RES 5,E
void res_5_e(void){
	regist.E=regist.E & 0xDF;
	reconstruirDE();
}

//0xac RES 5,H
void res_5_h(void){
	regist.H=regist.H & 0xDF;
	reconstruirHL();
}

//0xad RES 5,L
void res_5_l(void){
	regist.L=regist.L & 0xDF;
	reconstruirHL();
}

//0xae RES 5,(HL)
void res_5_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xDF);
	writeMEMB(regist.HL, ByteMEM);
}

//0xaf RES 5,A
void res_5_a(void){
	regist.A=regist.A & 0xDF;
}

//0xb0 RES 6,B
void res_6_b(void){
	regist.B=regist.B & 0xBF;
	reconstruirBC();
}

//0xb1 RES 6,C
void res_6_c(void){
	regist.C=regist.C & 0xBF;
	reconstruirBC();
}

//0xb2 RES 6,D
void res_6_d(void){
	regist.D=regist.D & 0xBF;
	reconstruirDE();
}

//0xb3 RES 6,E
void res_6_e(void){
	regist.E=regist.E & 0xBF;
	reconstruirDE();
}

//0xb4 RES 6,H
void res_6_h(void){
	regist.H=regist.H & 0xBF;
	reconstruirHL();
}

//0xb5 RES 6,L
void res_6_l(void){
	regist.L=regist.L & 0xBF;
	reconstruirHL();
}

//0xb6 RES 6,(HL)
void res_6_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0xBF);
	writeMEMB(regist.HL, ByteMEM);
}

//0xb7 RES 6,A
void res_6_a(void){
	regist.A=regist.A & 0xBF;
}

//0xb8 RES 7,B
void res_7_b(void){
	regist.B=regist.B & 0x7F;
	reconstruirBC();
}

//0xb9 RES 7,C
void res_7_c(void){
	regist.C=regist.C & 0x7F;
	reconstruirBC();
}

//0xba RES 7,D
void res_7_d(void){
	regist.D=regist.D & 0x7F;
	reconstruirDE();
}

//0xbb RES 7,E
void res_7_e(void){
	regist.E=regist.E & 0x7F;
	reconstruirDE();
}

//0xbc RES 7,H
void res_7_h(void){
	regist.H=regist.H & 0x7F;
	reconstruirHL();
}

//0xbd RES 7,L
void res_7_l(void){
	regist.L=regist.L & 0x7F;
	reconstruirHL();
}

//0xbe RES 7,(HL)
void res_7_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) & 0x7F);
	writeMEMB(regist.HL, ByteMEM);
}

//0xbf RES 7,A
void res_7_a(void){
	regist.A=regist.A & 0x7F;
}

//0xc0 SET 0,B
void set_0_b(void){
	regist.B=regist.B | 0x01;
	reconstruirBC();
}

//0xc1 SET 0,C
void set_0_c(void){
	regist.C=regist.C | 0x01;
	reconstruirBC();
}

//0xc2 SET 0,D
void set_0_d(void){
	regist.D=regist.D | 0x01;
	reconstruirDE();
}

//0xc3 SET 0,E
void set_0_e(void){
	regist.E=regist.E | 0x01;
	reconstruirDE();
}

//0xc4 SET 0,H
void set_0_h(void){
	regist.H=regist.H | 0x01;
	reconstruirHL();
}

//0xc5 SET 0,L
void set_0_l(void){
	regist.L=regist.L | 0x01;
	reconstruirHL();
}

//0xc6 SET 0,(HL)
void set_0_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x01);
	writeMEMB(regist.HL, ByteMEM);
}

//0xc7 SET 0,A
void set_0_a(void){
	regist.A=regist.A | 0x01;
}

//0xc8 SET 1,B
void set_1_b(void){
	regist.B=regist.B | 0x02;
	reconstruirBC();
}

//0xc9 SET 1,C
void set_1_c(void){
	regist.C=regist.C | 0x02;
	reconstruirBC();
}

//0xca SET 1,D
void set_1_d(void){
	regist.D=regist.D | 0x02;
	reconstruirDE();
}

//0xcb SET 1,E
void set_1_e(void){
	regist.E=regist.E | 0x02;
	reconstruirDE();
}

//0xcc SET 1,H
void set_1_h(void){
	regist.H=regist.H | 0x02;
	reconstruirHL();
}

//0xcd SET 1,L
void set_1_l(void){
	regist.L=regist.L | 0x02;
	reconstruirHL();
}

//0xce SET 1,(HL)
void set_1_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x02);
	writeMEMB(regist.HL, ByteMEM);
}

//0xcf SET 1,A
void set_1_a(void){
	regist.A=regist.A | 0x02;
}

//0xd0 SET 2,B
void set_2_b(void){
	regist.B=regist.B | 0x04;
	reconstruirBC();
}

//0xd1 SET 2,C
void set_2_c(void){
	regist.C=regist.C | 0x04;
	reconstruirBC();
}

//0xd2 SET 2,D
void set_2_d(void){
	regist.D=regist.D | 0x04;
	reconstruirDE();
}

//0xd3 SET 2,E
void set_2_e(void){
	regist.E=regist.E | 0x04;
	reconstruirDE();
}

//0xd4 SET 2,H
void set_2_h(void){
	regist.H=regist.H | 0x04;
	reconstruirHL();
}

//0xd5 SET 2,L
void set_2_l(void){
	regist.L=regist.L | 0x04;
	reconstruirHL();
}

//0xd6 SET 2,(HL)
void set_2_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x04);
	writeMEMB(regist.HL, ByteMEM);
}

//0xd7 SET 2,A
void set_2_a(void){
	regist.A=regist.A | 0x04;
}

//0xd8 SET 3,B
void set_3_b(void){
	regist.B=regist.B | 0x08;
	reconstruirBC();
}

//0xd9 SET 3,C
void set_3_c(void){
	regist.C=regist.C | 0x08;
	reconstruirBC();
}

//0xda SET 3,D
void set_3_d(void){
	regist.D=regist.D | 0x08;
	reconstruirDE();
}

//0xdb SET 3,E
void set_3_e(void){
	regist.E=regist.E | 0x08;
	reconstruirDE();
}

//0xdc SET 3,H
void set_3_h(void){
	regist.H=regist.H | 0x08;
	reconstruirHL();
}

//0xdd SET 3,L
void set_3_l(void){
	regist.L=regist.L | 0x08;
	reconstruirHL();
}

//0xde SET 3,(HL)
void set_3_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x08);
	writeMEMB(regist.HL, ByteMEM);
}

//0xdf SET 3,A
void set_3_a(void){
	regist.A=regist.A | 0x08;
}

//0xe0 SET 4,B
void set_4_b(void){
	regist.B=regist.B | 0x10;
	reconstruirBC();
}

//0xe1 SET 4,C
void set_4_c(void){
	regist.C=regist.C | 0x10;
	reconstruirBC();
}

//0xe2 SET 4,D
void set_4_d(void){
	regist.D=regist.D | 0x10;
	reconstruirDE();
}

//0xe3 SET 4,E
void set_4_e(void){
	regist.E=regist.E | 0x10;
	reconstruirDE();
}

//0xe4 SET 4,H
void set_4_h(void){
	regist.H=regist.H | 0x10;
	reconstruirHL();
}

//0xe5 SET 4,L
void set_4_l(void){
	regist.L=regist.L | 0x10;
	reconstruirHL();
}

//0xe6 SET 4,(HL)
void set_4_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x10);
	writeMEMB(regist.HL, ByteMEM);
}

//0xe7 SET 4,A
void set_4_a(void){
	regist.A=regist.A | 0x10;
}

//0xe8 SET 5,B
void set_5_b(void){
	regist.B=regist.B | 0x20;
	reconstruirBC();
}

//0xe9 SET 5,C
void set_5_c(void){
	regist.C=regist.C | 0x20;
	reconstruirBC();
}

//0xea SET 5,D
void set_5_d(void){
	regist.D=regist.D | 0x20;
	reconstruirDE();
}

//0xeb SET 5,E
void set_5_e(void){
	regist.E=regist.E | 0x20;
	reconstruirDE();
}

//0xec SET 5,H
void set_5_h(void){
	regist.H=regist.H | 0x20;
	reconstruirHL();
}

//0xed SET 5,L
void set_5_l(void){
	regist.L=regist.L | 0x20;
	reconstruirHL();
}

//0xee SET 5,(HL)
void set_5_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x20);
	writeMEMB(regist.HL, ByteMEM);
}

//0xef SET 5,A
void set_5_a(void){
	regist.A=regist.A | 0x20;
}

//0xf0 SET 6,B
void set_6_b(void){
	regist.B=regist.B | 0x40;
	reconstruirBC();
}

//0xf1 SET 6,C
void set_6_c(void){
	regist.C=regist.C | 0x40;
	reconstruirBC();
}

//0xf2 SET 6,D
void set_6_d(void){
	regist.D=regist.D | 0x40;
	reconstruirDE();
}

//0xf3 SET 6,E
void set_6_e(void){
	regist.E=regist.E | 0x40;
	reconstruirDE();
}

//0xf4 SET 6,H
void set_6_h(void){
	regist.H=regist.H | 0x40;
	reconstruirHL();
}

//0xf5 SET 6,L
void set_6_l(void){
	regist.L=regist.L | 0x40;
	reconstruirHL();
}

//0xf6 SET 6,(HL)
void set_6_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x40);
	writeMEMB(regist.HL, ByteMEM);
}

//0xf7 SET 6,A
void set_6_a(void){
	regist.A=regist.A | 0x40;
}

//0xf8 SET 7,B
void set_7_b(void){
	regist.B=regist.B | 0x80;
	reconstruirBC();
}

//0xf9 SET 7,C
void set_7_c(void){
	regist.C=regist.C | 0x80;
	reconstruirBC();
}

//0xfa SET 7,D
void set_7_d(void){
	regist.D=regist.D | 0x80;
	reconstruirDE();
}

//0xfb SET 7,E
void set_7_e(void){
	regist.E=regist.E | 0x80;
	reconstruirDE();
}

//0xfc SET 7,H
void set_7_h(void){
	regist.H=regist.H | 0x80;
	reconstruirHL();
}

//0xfd SET 7,L
void set_7_l(void){
	regist.L=regist.L | 0x80;
	reconstruirHL();
}

//0xfe SET 7,(HL)
void set_7_hl(void){
	reconstruirHL();
	unsigned char ByteMEM=(loadMEMB(regist.HL) | 0x80);
	writeMEMB(regist.HL, ByteMEM);
}

//0xff SET 7,A
void set_7_a(void){
	regist.A=regist.A | 0x80;
}