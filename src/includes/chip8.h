#ifndef CHIP8_H
#define CHIP8_H

#include "./config.h"
#include "./chip8memory.h"
#include "chip8registers.h"

struct chip8
{
    struct memory memory;
    struct registers registers;
};

#endif
