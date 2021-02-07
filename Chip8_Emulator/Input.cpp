#include "Input.h"



Input::Input()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
}

int Input::poll(void)
{
	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_KEYDOWN) {
		key_vector = 0;
		switch (e.key.keysym.sym) {
		case SDLK_1:
			cout << "yay1" << endl;
			key_vector |= 1 << 0;
		case SDLK_2:
			cout << "yay1" << endl;
			key_vector |= 1 << 1;
		}
	}
	return key_vector;
}	
