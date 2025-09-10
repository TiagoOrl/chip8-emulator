#include "./includes/chip8memory.h"
#include <assert.h>

static void is_memory_in_bounds(int index)
{
    assert(index >= 0 && index < CHIP8_MEM_SIZE);
}


void chip8_memory_set(struct memory * memory, int index, char val)
{
    is_memory_in_bounds(index);
    memory->memory[index] = val;
}


unsigned char chip8_memory_get(struct memory * memory, int index)
{
    is_memory_in_bounds(index);
    return memory->memory[index];
}
