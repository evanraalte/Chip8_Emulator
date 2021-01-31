#include "Memory.h"

Memory::Memory(size_t size)
	: mem(size,0)
{
	
}

void Memory::write(uint16_t address, uint8_t data)
{
	mem[address] = data;
}

uint8_t Memory::read(uint16_t address)
{
	return mem[address];
}
