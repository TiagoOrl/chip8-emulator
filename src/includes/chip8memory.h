#ifndef CHIP8_MEM_H
#define CHIP8_MEM_H

#include "./config.h"


struct memory
{
    unsigned char memory[CHIP8_MEM_SIZE];
};


void chip8_memory_set(struct memory * memory, int index, char val);
unsigned char chip8_memory_get(struct memory * memory, int index);
unsigned short chip8_memory_get_short(struct memory * memory, int index);

#endif
