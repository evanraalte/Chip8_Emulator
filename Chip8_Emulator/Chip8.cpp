#include "Chip8.h"





Chip8::Chip8(void)
	: mem(4096) {

	// Initialize fonts in memory
	Font font = Font();
	uint16_t idx = 0;
	for (auto & d : font.data) {
		mem.write(idx, d);
		idx += 1;
	}

}


