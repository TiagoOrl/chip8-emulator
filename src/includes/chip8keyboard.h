#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H

#include "./config.h"
#include <stdbool.h>

struct keyboard 
{
	bool keyboard[TOTAL_KEYS];
};


int chip8_keyboard_map(char in_key);
void chip8_keyboard_down(struct keyboard* keyboard, char in_key);
void chip8_keyboard_up(struct keyboard* keyboard, char in_key);
bool chip8_keyboard_is_down(struct keyboard* keyboard, int in_key);


#endif