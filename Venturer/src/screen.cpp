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
	this->resX = width;
	this->resY = height;
}

//destructor
Screen::~Screen() {
	//renderer
	SDL_DestroyRenderer(this->renderer);
	//window
	SDL_DestroyWindow(this->window);
}

//prep text
void Screen::prepText(const char* textString, int widthCap, int fontSize) {
	this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", fontSize), textString, { 190,190,190 }, widthCap);
	this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}

//prep image
void Screen::prepImg(const char* imgPath) {
	this->surface = IMG_Load(imgPath);
	this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}

//draw page
void Screen::drawPage(bool printImg, SDL_Rect txtRect, SDL_Rect imgRect) {
	//draw text to screen
	SDL_RenderCopy(this->renderer, this->txtTexture, NULL, &txtRect);
	SDL_RenderPresent(this->renderer);
	//draw image to screen
	if (printImg == true) {
		SDL_RenderCopy(this->renderer, this->imgTexture, NULL, &imgRect);
		SDL_RenderPresent(this->renderer);
	}
}