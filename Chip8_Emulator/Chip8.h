#pragma once
#include "std_lib_facilities.h"
#include "Memory.h"
#include "Font.h"
#include "Display.h"
#include "Input.h"
// Follow: https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

//class Display;

class Chip8
{
public:
	Display display;
	Chip8(void);
	uint16_t stack_pop();
	void stack_push(uint16_t data);
	void decrement_timers(void);
	void run(void);
	Memory mem;
	uint16_t pc;
	uint16_t reg_i;
	vector<uint16_t> stack;
	uint8_t delay_timer;
	uint8_t sound_timer;
	array<uint8_t, 16> v;
	static map<int, int> key_map;
	array<array<bool, 32>, 64> frame_buffer;
	void load_file(string path);
	bool get_pixel(int x, int y);
};

