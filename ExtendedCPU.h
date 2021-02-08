#pragma once

struct CBinstruction {
	int valid_instruction;
	int clock_cycle;
	int machine_cycle;
	void (*action)(void);
	
	//unsigned char ticks;

} extern const CBinstructions[256];


static unsigned char rlc(unsigned char registro);
static unsigned char rrc(unsigned char registro);
static unsigned char rl(unsigned char registro);
static unsigned char rr(unsigned char registro);
static unsigned char sla(unsigned char registro);


void rlc_b(void);
void rlc_c(void);
void rlc_d(void);
void rlc_e(void);
void rlc_h(void);
void rlc_l(void);
void rlc_hl(void);
void rlc_a(void);
void rrc_b(void);
void rrc_c(void);
void rrc_d(void);
void rrc_e(void);
void rrc_h(void);
void rrc_l(void);
void rrc_hl(void);
void rrc_a(void);
void rl_b(void);
void rl_c(void);
void rl_d(void);
void rl_e(void);
void rl_h(void);
void rl_l(void);
void rl_hl(void);
void rl_a(void);
void rr_b(void);
void rr_c(void);
void rr_d(void);
void rr_e(void);
void rr_h(void);
void rr_l(void);
void rr_hl(void);
void rr_a(void);
void sla_b(void);
void sla_c(void);
void sla_d(void);
void sla_e(void);
void sla_h(void);
void sla_l(void);
void sla_hl(void);
void sla_a(void);