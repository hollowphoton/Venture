/*
SCREEN CLASS
This class controls SDL, including:
-game window
-drawing graphics
-drawing text
*/

//headers
#include "headers/screen.h"

//constructor
Screen::Screen(const char* title, int width, int height) {
	//window & renderer
	SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);
	//set window title
	SDL_SetWindowTitle(this->window, title);
}

//destructor
Screen::~Screen() {
	//renderer
	SDL_DestroyRenderer(this->renderer);
	//window
	SDL_DestroyWindow(this->window);
}