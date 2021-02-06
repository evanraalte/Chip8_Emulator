#include "Display.h"
#include "Chip8.h"

Display::Display(Chip8& parent)
 : c8(parent){
	init();
}

Display::~Display()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

int Display::init(void) {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			}
		}
	}
	return success;
}


void Display::draw_pixel(int x, int y, bool on) {
	//Render red filled quad

	SDL_Rect fillRect = { x*10, y*10, 10, 10 };
	uint8_t fill = on ? 0xFF : 0x00;
	SDL_SetRenderDrawColor(gRenderer, fill, fill, fill, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

void Display::render_frame()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 32; y++) {
			draw_pixel(x, y, c8.get_pixel(x,y));
		}
	}
	SDL_RenderPresent(gRenderer);
	return;
}
