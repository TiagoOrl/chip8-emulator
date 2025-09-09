#ifndef CHIP8_MEM_H
#define CHIP8_MEM_H

#include "./config.h"


struct chip8_memory
{
    unsigned char memory[CHIP8_MEM_SIZE];
};


void chip8_memory_set(struct chip8_memory* memory, int index, char val);
unsigned char chip8_memory_get(struct chip8_memory* memory, int index);


#endif
