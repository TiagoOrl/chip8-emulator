#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H

#include "./config.h"

struct registers
{
    unsigned char V[DATA_REGISTERS_COUNT];  // 8 bit register
    unsigned short I; // 16 bit register
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short VF;
    unsigned short PC;
    unsigned char SP;
};

#endif