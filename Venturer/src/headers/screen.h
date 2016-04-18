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

//screen manager class
class Screen
{
public:
	//vars
	SDL_Surface* surface;
	SDL_Texture* backTexture;
	SDL_Texture* txtTexture;
	SDL_Texture* imgTexture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect txtRect;
	SDL_Rect imgRect;
	int resX;
	int resY;
	//methods
	Screen(const char* windowTitle, int width, int height); //constructor
	~Screen(); //destructor
	void prepText(const char* textString, int widthCap, int fontSize);
	void prepImg(const char* imgPath);
	void drawPage(bool hasImg, std::string imgPos, const char* imgPath, const char* textString, std::vector<Choice> choices);
	void draw2screen(bool printImg, SDL_Rect txtRect, SDL_Rect imgRect);
private:
};

#endif