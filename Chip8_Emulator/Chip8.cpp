#include "Chip8.h"


Chip8::Chip8(void)
	: mem(4096), display(*this) {


	// Init button poller
	//thread t_inp(&Display::poll_input, display);
	//t_inp.join();
	//while (true) {
	//	display.poll_input();
	//}

	// Init frame_buffer
	for (uint16_t i = 0; i < frame_buffer.size(); i++) {
		bool fill = false;
		frame_buffer[i].fill(fill);
	}
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
	pc    = 0x0200;
	reg_i = 0x0000;

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

void Chip8::run(void)
{
	while (true) {
		//cout << to_string(pc) << endl;
		// Fetch
		uint16_t msb = (uint16_t)mem.read(pc);
		uint16_t lsb = (uint16_t)mem.read(pc + 1);
		pc += 2;
		uint16_t instruction = (msb << 8) | lsb;

		// Decode
		uint8_t opc = (0xF000 & instruction) >> 12;
		uint8_t x = (0x0F00 & instruction) >> 8;
		uint8_t y = (0x00F0 & instruction) >> 4;
		uint8_t n = (0x000F & instruction);
		uint8_t nn = (0x00FF & instruction);
		uint16_t nnn = (0x0FFF & instruction);

		// Execute
		switch (opc) {
		case 0x0:
			if (nn == 0xE0) {

				//cout << "clear screen" << endl;
				// clear screen
			}
			break;
		case 0x1:
			//cout << "jump to " << to_string((int)nnn) << endl;
			pc = nnn;
			break;
		case 0x6:
			//cout << "set v[" << to_string((int)x) << "] to " << to_string((int)nn) << endl;
			v[x] = nn;
			break;
		case 0x7:
			//cout << "set v[" << to_string((int)x) << "] to " << to_string((int)(v[x] + nn)) << endl;
			v[x] += nn;
			break;
		case 0xA:
			//cout << "set I to " << to_string((int)nnn) << endl;
			reg_i = nnn;
			break;
		case 0xD:
			// draw
			//cout << "Draw.." << endl;
			for (int j = 0; j < n; j++) {
				v[0xf] = 0;
				uint8_t pos_y = (v[y] & 0x1F) + j;
				uint8_t pos_x = v[x] & 0x3F;
				uint8_t sprite_data = mem.read(reg_i + j);
				for (int i = 7; i >= 0; i--) {
					bool px_data = (sprite_data >> i) & 0x1;

					if (px_data) {
						if (frame_buffer[pos_x][pos_y]) {
							frame_buffer[pos_x][pos_y] = false;
							v[0xf] = 1;
						}
						else {
							frame_buffer[pos_x][pos_y] = true;
						}
					}
					pos_x++;
					if (pos_x >= 64)
						break;
				}
			}
			display.render_frame();
			break;
		}
		display.get_keystate();
		this_thread::sleep_for(chrono::microseconds(16667));
	}
}

void Chip8::load_file(string path)
{
	ifstream f(path, ios::in | ios::binary);
	char buffer;
	uint16_t address = 0x200;
	while (f) {
		f.read(&buffer, 1);
		cout << to_string((int) buffer) << endl;
		mem.write(address, (uint8_t) buffer);
		address++;
	}
	f.close();
}

bool Chip8::get_pixel(int x, int y)
{
	return frame_buffer[x][y];
}


