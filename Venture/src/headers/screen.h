/*
SCREEN.H
This is the header file for the screen class
*/

#ifndef SCREEN_H
#define SCREEN_H

//headers
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "headers/global.h"
#include "headers/book.h"
#include <string>
#include <vector>


//-----------------------screen class------------------------//
class Screen
{
public:
	//vars
	SDL_Surface* surface;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int resX;
	int resY;
	//methods
	Screen(const char* windowTitle, int width, int height); //constructor
	~Screen(); //destructor
	
	void renderSurface(SDL_Texture* thing, SDL_Rect place);
	void cleanScreen();
private:
};

#endif