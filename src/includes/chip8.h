#ifndef CHIP8_H
#define CHIP8_H

#include "./config.h"
#include "./chip8memory.h"
#include "./chip8registers.h"
#include "./chip8stack.h"
#include "./chip8keyboard.h"

struct chip8
{
    struct memory memory;
    struct stack stack;
    struct registers registers;
    struct keyboard keyboard;
};

#endif
