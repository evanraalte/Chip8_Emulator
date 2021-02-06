#pragma once
#include "std_lib_facilities.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>

class Chip8;

class Display
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 320;
	Chip8& c8;
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	array<array<bool, 32>, 64>* frame_buffer = NULL;
	//The window renderer
	SDL_Renderer* gRenderer = NULL;
public:
	Display(Chip8& objChip8);
	~Display();
	int init(void);
	void draw_pixel(int x, int y, bool on);
	void render_frame();
	void run(void);

};

