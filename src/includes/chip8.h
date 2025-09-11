#ifndef CHIP8_H
#define CHIP8_H

#include "./config.h"
#include "./chip8memory.h"
#include "./chip8registers.h"
#include "./chip8stack.h"
#include "./chip8keyboard.h"
#include "./chip8screen.h"

struct chip8
{
    struct memory memory;
    struct stack stack;
    struct registers registers;
    struct keyboard keyboard;
    struct screen screen;
};


void chip8_init(struct chip8* chip8);

#endif
