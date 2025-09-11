#include "./includes/chip8keyboard.h"
#include <assert.h>
#include <stdio.h>

const char keyboard_map[TOTAL_KEYS] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'
};

static void chip8_keyboard_ensure_in_bounds(int key)
{
	assert(key >= 0 && key < TOTAL_KEYS);
}


int chip8_keyboard_map(const char* map, char key)
{
	for (int i = 0; i < TOTAL_KEYS; i++)
	{
		if (map[i] == key)
		{
			return i;
		}
	}

	return -1;
}


void chip8_keyboard_down(struct keyboard* keyboard, char in_key)
{
	int out_key = chip8_keyboard_map(keyboard_map, in_key);

	if (out_key != -1)
		keyboard->keyboard[out_key] = true;
}


void chip8_keyboard_up(struct keyboard* keyboard, char in_key)
{
	int out_key = chip8_keyboard_map(keyboard_map, in_key);

	if (out_key != -1)
		keyboard->keyboard[out_key] = false;
}



bool chip8_keyboard_is_down(struct keyboard* keyboard,int key)
{
	return keyboard->keyboard[key];
}