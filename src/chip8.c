#include "./includes/chip8.h"
#include <memory.h>
#include <assert.h>
#include <stdbool.h>


const char chip8_default_char_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xf0, 0x10, 0x10, // 4
    0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xf0, 0x90, 0xf0, // 8
    0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
    0xf0, 0x90, 0xf0, 0x90, 0x90, // a
    0xe0, 0x90, 0xe0, 0x90, 0xe0, // b
    0xF0, 0x80, 0x80, 0x80, 0xF0, // c
    0xE0, 0x90, 0x90, 0x90, 0xE0, // d
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // e
    0xF0, 0x80, 0xF0, 0x80, 0x80 // f
};


void chip8_init(struct chip8* chip8)
{
    memset(chip8, 0, sizeof(struct chip8));
    memcpy(&chip8->memory.memory, chip8_default_char_set, sizeof(chip8_default_char_set));
}


void chip8_load(struct chip8 * chip8, const char * buf, size_t size)
{
    assert(size + CHIP8_PROGRAM_LOAD_ADDRESS < CHIP8_MEM_SIZE);

    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;

}


static void chip8_exec_extended_eight(struct chip8 * chip8, unsigned short opcode)
{
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char final_four_bits = opcode & 0x000f;
    unsigned short tmp = 0;

    switch (final_four_bits)
    {   
        // 8xy0 - LD Vx, Vy -> Vx = Vy
        case 0x00:
            chip8->registers.V[x] = chip8->registers.V[y];
        break;

        // 8xy1 - OR Vx, Vy store in Vx
        case 0x01:
            chip8->registers.V[x] |= chip8->registers.V[y];
        break;


        // 8xy2 - AND Vx, Vy store in Vx
        case 0x02:
            chip8->registers.V[x] &= chip8->registers.V[y];
        break;

        // 8xy3 - XOR Vx, Vy store in Vx
        case 0x03:
            chip8->registers.V[x] ^= chip8->registers.V[y];
        break;

        // 8xy4 - ADD Vx, Vy store in Vx, set VF = carry
        case 0x04:
            tmp = chip8->registers.V[x] + chip8->registers.V[y];
            chip8->registers.V[0x0f] = false;

            if (tmp > 0xff)
                chip8->registers.V[0x0f] = true;
            
            chip8->registers.V[x] = tmp;
        break;
        
        // 8xy5 - SUB Vx, Vy : Vx = Vx - Vy : set VF = not borrow
        case 0x05:
            chip8->registers.V[0x0f] = false;

            if (chip8->registers.V[x] > chip8->registers.V[y])
                chip8->registers.V[0x0f] = true;

            chip8->registers.V[x] -= chip8->registers.V[y];
        break;

        // 8xy6 - SHR Vx {, Vy}0
        case 0x06:
            chip8->registers.V[0x0f] = chip8->registers.V[x] & 0x01;
            chip8->registers.V[x] /= 2;
        break;

        // 8xy7 - SUBN Vx, Vy:  Vx = Vy - Vx set VF NOT borrow
        case 0x07:
            chip8->registers.V[0x0f] = chip8->registers.V[y] > chip8->registers.V[x];
            chip8->registers.V[x] = chip8->registers.V[y] - chip8->registers.V[x];
        break;

        // 8xye : SHL Vx {, Vy}
        case 0x0e:
            chip8->registers.V[0x0f] = chip8->registers.V[x] & 0b10000000;
            chip8->registers.V[x] *= 2;
        break;

    }
}


static void chip8_exec_extended_nine(struct chip8 * chip8, unsigned short opcode)
{
    
}


static void chip8_exec_extended(struct chip8 * chip8, unsigned short opcode)
{
    // get the last 12 bits
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char kk = opcode & 0x00ff;


    switch (opcode & 0xf000)
    {
        // JP Address, 1nnn Jump to location nnn
        case 0x1000:
            chip8->registers.PC = nnn;
        break;

        // call addr, 2nnn call subroutine at location nnn
        case 0x2000:
            chip8_stack_push(chip8, chip8->registers.PC);
            chip8->registers.PC = nnn;
        break;

        // SE Vx, byte = 3xkk skip next instruction if Vx = kk
        case 0x3000:
            if (chip8->registers.V[x] == kk)
            {
                chip8->registers.PC += 2; // skips the next instruction
            }

        break;
        
        // SNE Vx, byte = 3xkk skip next instruction if Vx != kk
        case 0x4000:
            if (chip8->registers.V[x] != kk)
            {
                chip8->registers.PC += 2; // skips the next instruction
            }

        break;

        // 5xy0 = SE \vx Vy, skip the next instruction if Vx == Vy
        case 0x5000:
            if (chip8->registers.V[x] == chip8->registers.V[y])
            {
                chip8->registers.PC += 2; // skips the next instruction
            }
        break;

        // 6xkk LD Vx, byte - Vx == kk
        case 0x6000:
            chip8->registers.V[x] = kk;
        break;  

        // 7xkk - add Vx, byte. Set Vx = Vx + kk
        case 0x7000:
            chip8->registers.V[x] += kk;
        break;

        case 0x8000:
            chip8_exec_extended_eight(chip8, opcode);
        break;

        case 0x9000:
            chip8_exec_extended_nine(chip8, opcode);
        break;
    }
}


void chip8_exec(struct chip8 * chip8, unsigned short opcode)
{
    switch (opcode)
    {   
        // cls: clear the display
        case 0x00e0:
            chip8_screen_clear(&chip8->screen);
        break;

        // ret: return from subroutine
        case 0x00ee:
            chip8->registers.PC = chip8_stack_pop(chip8);
        break;

        default:
            chip8_exec_extended(chip8, opcode);
    }
}