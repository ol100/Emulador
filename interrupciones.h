#pragma once

extern unsigned char master;
extern unsigned char activado;
extern unsigned char flags;
extern unsigned char halto;
extern int m_DividerVariable;
extern int m_TimerVariable;
extern int m_CurrentClockSpeed;

void vectorInterrupcion();
void vblankInterrupcion();
void lcdstatInterrupcion();
void timerInterrupcion();
void serialInterrupcion();
void joypadInterrupcion();
void Timer(int ciclos);

void ServiceInterrupt(int num);
bool TestBit(unsigned short address, int bit);
unsigned char BitReset(unsigned char addr, int position);

void volverInterrupcion();