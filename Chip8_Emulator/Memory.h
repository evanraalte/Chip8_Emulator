#pragma once
#include "std_lib_facilities.h"

class Memory {
public:
    Memory(size_t size);
    void write(uint16_t address, uint8_t data);
    uint8_t read(uint16_t address);
private:
    vector<uint8_t> mem;
};