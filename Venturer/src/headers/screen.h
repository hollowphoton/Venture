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
#include <string>

//screen manager class
class Screen
{
public:
	//vars
	SDL_Surface* surface;
	SDL_Texture* txtTexture;
	SDL_Texture* imgTexture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int resX;
	int resY;
	//methods
	Screen(const char* windowTitle, int width, int height); //constructor
	~Screen(); //destructor
	void prepText(const char* textString, int widthCap, int fontSize);
	void prepImg(const char* imgPath);
	void drawPage(bool printImg, SDL_Rect txtRect, SDL_Rect imgRect);
private:
};

#endif