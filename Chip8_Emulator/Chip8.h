#pragma once
#include "std_lib_facilities.h"
#include "Memory.h"
#include "Font.h"

class Chip8
{
public:
	Chip8(void);
	Memory mem;
private:
	static array<uint8_t, 80> font_data;
};

