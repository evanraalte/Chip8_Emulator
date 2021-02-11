#include "Chip8.h"


void Chip8::clear_display(void)
{
	for (uint16_t i = 0; i < frame_buffer.size(); i++) {
		bool fill = false;
		frame_buffer[i].fill(fill);
	}
}

Chip8::Chip8(void)
	: mem(4096), display(*this) {


	// Init button poller
	//thread t_inp(&Display::poll_input, display);
	//t_inp.join();
	//while (true) {
	//	display.poll_input();
	//}

	// Init frame_buffer
	//for (uint16_t i = 0; i < frame_buffer.size(); i++) {
	//	bool fill = false;
	//	frame_buffer[i].fill(fill);
	//}
	clear_display();
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
		decrement_timers();
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
			switch(nnn){
			case 0x0E0:
				clear_display();
				display.render_frame();
				break;
			case 0x0EE: // return from subroutine
				pc = stack.back();
				stack.pop_back();
				break;
			}
			break;
		case 0x1:
			//cout << "jump to " << to_string((int)nnn) << endl;
			pc = nnn;
			break;
		case 0x2:
			stack.push_back(pc);
			pc = nnn;
			break;
		case 0x3:
			if (v[x] == nn)
				pc += 2;
			break;
		case 0x4:
			if (v[x] != nn)
				pc += 2;
			break;
		case 0x5:
			if (v[x] == v[y])
				pc += 2;
			break;
		case 0x6:
			//cout << "set v[" << to_string((int)x) << "] to " << to_string((int)nn) << endl;
			v[x] = nn;
			break;
		case 0x7:
			//cout << "set v[" << to_string((int)x) << "] to " << to_string((int)(v[x] + nn)) << endl;
			v[x] += nn;
			break;
		case 0x8:
			switch (n) {
			case 0:
				v[x] = v[y];
				break;
			case 1:
				v[x] = v[x] | v[y];
				break;
			case 2:
				v[x] = v[x] & v[y];
				break;
			case 3:
				v[x] = v[x] ^ v[y];
				break;
			case 4:
				v[0xf] = ((uint16_t)v[x] + (uint16_t)v[y] > 0xFF) ? 1 : 0;
				v[x] = v[x] + v[y];
				break;
			case 5:
				v[0xf] = (v[x] > v[y]) ? 1 : 0;
				v[x] = v[x] - v[y];
				break;
			case 6:
				v[x] = 0xFF & (v[y] >> 1);
				v[0xf] = (uint8_t) (v[y] & 0x01);
				break;
			case 7:
				v[0xf] = (v[x] > v[y]) ? 1 : 0;
				v[x] = v[y] - v[x];
				break;
			case 0xE:
				v[x] = 0xFF & (v[y] << 1);
				v[0xf] = (uint8_t)((v[y] & 0x80) == 0x80);
				break;
			}
		case 0x9:
			if (v[x] != v[y])
				pc += 2;
			break;
		case 0xA:
			//cout << "set I to " << to_string((int)nnn) << endl;
			reg_i = nnn;
			break;
		case 0xB:
			pc = nnn + v[0];
			break;
		case 0xC:
			v[x] = rand() & nn;
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
		case 0xE:
		{
			uint16_t key_num = 1 << v[x];
			switch (nn) {
			case 0x9e:
				if ((display.get_keystate() & key_num) == key_num)
					pc += 2;
				break;
			case 0xa1:
				if ((display.get_keystate() & key_num) != key_num)
					pc += 2;
				break;
			}
		}
		break;
		case 0xF:
			switch (nn) {
			case 0x07:
				v[x] = delay_timer;
				break;
			case 0x0a: 
			{
				uint16_t inp_old = display.get_keystate();
				uint16_t inp = display.get_keystate();
				while (inp == inp_old) {
					inp_old = inp;
					inp = display.get_keystate();
				}
				inp = inp - inp_old;
				uint8_t  cnt = 0;
				uint16_t  comparee = 0x0001;
				while (comparee != inp) {
					cnt++;
					comparee = comparee << 1;
					if (cnt == 16)
						break;
				}
				v[x] = cnt;
			}
			break;
			case 0x15:
				delay_timer = v[x];
				break;
			case 0x18:
				sound_timer = v[x];
				break;
			case 0x1e:
				reg_i += v[x];
				v[0xf] = (uint16_t)(reg_i > 0xFFF);
				reg_i = reg_i & 0xFFF;
				break;
			case 0x29:
				reg_i = v[x]*5;
				break;
			case 0x33:
				mem.write(reg_i + 0, v[x] / 100);
				mem.write(reg_i + 1, (v[x] % 100) / 10);
				mem.write(reg_i + 2, v[x] % 10);
				break;
			case 0x55:
				for (int i = 0; i <= x; i++) {
					mem.write(reg_i + i, v[i]);
				}
				reg_i = reg_i + x + 1;
				break;
			case 0x65:
				for (int i = 0; i <= x; i++) {
					v[i] = mem.read(reg_i + i);
				}
				reg_i = reg_i + x + 1;
				break;
			}
		}
		this_thread::sleep_for(chrono::microseconds(1666));
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


