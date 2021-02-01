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

void Chip8::decrement_timers(void)
{
	delay_timer = (delay_timer > 0) ? (delay_timer - 1) : delay_timer;
	sound_timer = (sound_timer > 0) ? (sound_timer - 1) : sound_timer;
}

void Chip8::run(int val)
{
	while (true) {
		this_thread::sleep_for(chrono::seconds(1));
		cout << "running" << endl << flush;
	}
}

void Chip8::cb_input(int c)
{
	cout << "Pressed: " << to_string(c) << endl << flush;
}


