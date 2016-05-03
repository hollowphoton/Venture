/*
SCREEN CLASS
This class controls SDL, including:
-game window
-drawing graphics
-drawing text
*/

//headers
#include "headers/screen.h"

//--------------------------------------screen methods--------------------------------------//

	//constructor
	Screen::Screen(const char* title, int width, int height) {
		//window & renderer
		SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);
		//set window title
		SDL_SetWindowTitle(this->window, title);
		this->resX = width;
		this->resY = height;
		//draw background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
	}

	//destructor
	Screen::~Screen() {
		//renderer
		SDL_DestroyRenderer(this->renderer);
		//window
		SDL_DestroyWindow(this->window);
	}

	//clean screen
	void Screen::cleanScreen() {
		//draw background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//clear surface
		SDL_FillRect(this->surface, NULL, 0x000000);
	}

	//draw to screen
	void Screen::draw2screen(SDL_Texture* thing, SDL_Rect place) {
		//draw text to screen
		SDL_RenderCopy(this->renderer, thing, NULL, &place);
		SDL_RenderPresent(this->renderer);
	}