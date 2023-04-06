#pragma once

extern unsigned char master;
extern unsigned char activado;
extern unsigned char flags;

void vectorInterrupcion();
void vblankInterrupcion();
void lcdstatInterrupcion();
void timerInterrupcion();
void serialInterrupcion();
void joypadInterrupcion();

void volverInterrupcion();