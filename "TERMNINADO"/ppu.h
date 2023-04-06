#pragma once

extern unsigned char scanline;
extern unsigned char lcdStatus;
extern unsigned char control;
extern unsigned char scrollX;
extern unsigned char scrollY;
extern unsigned char windowY;
extern unsigned char windowX;

void ejecutarPPU();
void setLCDStatus();
bool isLCDEnabled();