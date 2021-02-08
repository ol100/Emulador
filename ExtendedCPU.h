#pragma once

struct CBinstruction {
	int valid_instruction;
	int clock_cycle;
	int machine_cycle;
	void (*action)(void);
	
	//unsigned char ticks;

} extern const CBinstructions[256];