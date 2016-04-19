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
#include "headers/page.h"
#include <string>

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
	void drawPage(bool hasImg, pageLayout imgPos, pageType pgType, const char* imgPath, const char* textString, std::vector<Choice> choiceArray);
	void draw2screen(SDL_Texture* thing, SDL_Rect place);
private:
};

#endif