#pragma once
#include "std_lib_facilities.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>


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

//map<int, int> Chip8::key_map = {
//	{ KEY_1, 0x1 },
//	{ KEY_2, 0x2 },
//	{ KEY_3, 0x3 },
//	{ KEY_4, 0xC },
//	{ KEY_Q, 0x4 },
//	{ KEY_W, 0x5 },
//	{ KEY_E, 0x6 },
//	{ KEY_R, 0xD },
//	{ KEY_A, 0x7 },
//	{ KEY_S, 0x8 },
//	{ KEY_D, 0x9 },
//	{ KEY_F, 0xE },
//	{ KEY_Z, 0xA },
//	{ KEY_X, 0x0 },
//	{ KEY_C, 0xB },
//	{ KEY_V, 0xF },
//};


class Input
{
private:
	
	int key_vector = 0;
public:
	Input();
	int poll(void);
};

