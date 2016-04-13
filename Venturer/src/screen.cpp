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

//draw text
void Screen::prepText(const char* textString) {
	this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", 16), textString, { 190,190,190 }, 840);
	this->textTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}

//draw image
void Screen::prepImg(const char* imgPath) {
	this->surface = IMG_Load(imgPath);
	this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}