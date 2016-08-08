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
		//set window title & res & full screen
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

	//make text texture
	void Screen::makeTextTexture(const char* fontName, int fontSize, const char* textString, SDL_Color colorRGB, int maxWidth) {
		//draw text
		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont(fontName, fontSize), textString, colorRGB, maxWidth);
		//make texture
		this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	}

	//make image texture
	void Screen::makeImageTexture(const char* imgPath) {
		//draw text
		this->surface = IMG_Load(imgPath);
		//make texture
		this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	}

	//draw texture to buffer
	void Screen::drawTexture(SDL_Texture* thing, SDL_Rect place) {
		//draw text to screen
		SDL_RenderCopy(this->renderer, thing, NULL, &place);
	}

	//render buffer
	void Screen::renderBuffer() {
		SDL_RenderPresent(this->renderer);
	}