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

//prep text
void Screen::prepText(const char* textString, int widthCap, int fontSize) {
	this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", fontSize), textString, { 100,100,100 }, widthCap);
	this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}

//prep image
void Screen::prepImg(const char* imgPath) {
	this->surface = IMG_Load(imgPath);
	this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}

//prep page
void Screen::drawPage(bool hasImg, std::string imgPos, const char* imgPath, const char* textString, std::vector<Choice> choices) {

	//init vars
	int imgWidth; //image size x
	int imgHeight; //image size y
	int imgBuffer; //img vertical buffer
	double imgXYRatio; //img x/y ratio
	int txtSize; //txt font size
	int divider; //pixel size of divider between all screen elements
	int txtWidth; //text pixel width
	int txtHeight; //text pixel height
	int txtBuffer; //text vertical buffer
	int txtSpace; //allotted space that fits text

	//set divider & font size
	divider = this->resY / 36;
	txtSize = this->resY / 45;

	//prep img (if image exists)
	if (hasImg == true) {
		//draw image to surface
		this->surface = IMG_Load(imgPath);
		this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
		//get image resolution & ratio
		SDL_QueryTexture(this->imgTexture, NULL, NULL, &imgWidth, &imgHeight);
		imgXYRatio = (double(imgWidth) / double(imgHeight));
		//scale image to fill the same screen space
		imgWidth = int(this->resX / 3.2);
		imgHeight = int(imgWidth / imgXYRatio);
	}

	// calculate text space (window resX - 3 blank dividers of 20 pixels - imgWidth) - if no image, account for that
	if (hasImg == true) {
		txtSpace = this->resX - ((divider * 3) + imgWidth);
	}
	else {
		txtSpace = this->resX - (divider * 2);
	}

	//draw text to surface
	this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), textString, { 100,100,100 }, txtSpace);
	this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	//get text resolution
	SDL_QueryTexture(this->txtTexture, NULL, NULL, &txtWidth, &txtHeight);

	//adjust the placement of the text and image so they are centered
	//determine if there is an image - to account for centering
	if (hasImg == true) {
		//calculate text vertical buffer
		txtBuffer = ((this->resY - (divider * 2)) - txtHeight) / 2;
		//calculate text vertical buffer
		imgBuffer = ((this->resY - (divider * 2)) - imgHeight) / 2;
		//set text placement
		this->txtRect = { ((divider * 2) + imgWidth), txtBuffer, txtWidth, txtHeight };
		//set image placement
		this->imgRect = { divider, imgBuffer, imgWidth, imgHeight };
	}
	else {
		//calculate text vertical buffer
		txtBuffer = ((this->resY - (divider * 2)) - txtHeight) / 2;
		//set text placement
		this->txtRect = { txtBuffer, divider, txtWidth, txtHeight };
	}

	//call draw page
	this->draw2screen(hasImg, this->txtRect, this->imgRect);

}

//draw page
void Screen::draw2screen(bool printImg, SDL_Rect txtRect, SDL_Rect imgRect) {
	//draw text to screen
	SDL_RenderCopy(this->renderer, this->txtTexture, NULL, &txtRect);
	SDL_RenderPresent(this->renderer);
	//draw image to screen
	if (printImg == true) {
		SDL_RenderCopy(this->renderer, this->imgTexture, NULL, &imgRect);
		SDL_RenderPresent(this->renderer);
	}
}