#pragma once
#include "std_lib_facilities.h"
#include "Memory.h"
#include "Font.h"

// Follow: https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

class Chip8
{
public:
	Chip8(void);
	uint16_t stack_pop();
	void stack_push(uint16_t data);
	void decrement_timers(void);
	void run(int val);
	void cb_input(int c);
	Memory mem;
	uint16_t pc;
	uint16_t idx;
	vector<uint16_t> stack;
	uint8_t delay_timer;
	uint8_t sound_timer;
	array<uint8_t, 16> v;
};

