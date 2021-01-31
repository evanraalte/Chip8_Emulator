#include "Chip8.h"





Chip8::Chip8(void)
	: mem(4096) {

	// Initialize fonts in memory
	Font font = Font();
	uint16_t i = 0;
	for (auto & d : font.data) {
		mem.write(i, d);
		i += 1;
	}

	// Init registers
	for (int i = 0; i < v.size(); i++)
		v[i] = 0;
	pc  = 0x0200;
	idx = 0x0000;

	// Init timers
	delay_timer = 0;
	sound_timer = 0;
}

uint16_t Chip8::stack_pop()
{
	uint16_t res = stack.back();
	stack.pop_back();
	return res;
}

void Chip8::stack_push(uint16_t data)
{
	stack.push_back(data);
	return;
}


