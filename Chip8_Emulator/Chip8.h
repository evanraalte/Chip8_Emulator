#pragma once
#include "std_lib_facilities.h"
#include "Memory.h"
#include "Font.h"
#include "Display.h"
// Follow: https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

constexpr auto BLA = 27; // ESC

constexpr auto KEY_1 = 49; // ESC
constexpr auto KEY_2 = 50; // ESC
constexpr auto KEY_3 = 51; // ESC
constexpr auto KEY_4 = 52; // ESC
constexpr auto KEY_Q = 113; // ESC
constexpr auto KEY_W = 119; // ESC
constexpr auto KEY_E = 101; // ESC
constexpr auto KEY_R = 114; // ESC
constexpr auto KEY_A = 97;  // ESC
constexpr auto KEY_S = 115; // ESC
constexpr auto KEY_D = 100; // ESC
constexpr auto KEY_F = 102; // ESC
constexpr auto KEY_Z = 122; // ESC
constexpr auto KEY_X = 120; // ESC
constexpr auto KEY_C = 99;  // ESC
constexpr auto KEY_V = 118; // ESC


class Display;

class Chip8
{
public:
	Display display;
	Chip8(void);
	uint16_t stack_pop();
	void stack_push(uint16_t data);
	void decrement_timers(void);
	void run(void);
	void cb_input(int c);
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

