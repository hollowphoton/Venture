/*
GAME CLASS
This class controls the main game loop, including:
-menus
-intros
-credits
-main game loop
*/

//headers
#include "headers/game.h"
#include "headers/screen.h"
#include "headers/page.h"

//constructor
Game::Game() {

	//init SDL
		//video
		SDL_Init(SDL_INIT_VIDEO);
		//fonts
		TTF_Init();
		//img (png)
		IMG_Init(IMG_INIT_PNG);

	//start game loop
	this->gameLoop();
}

//destructor
Game::~Game() {

}

//game loop
void Game::gameLoop() {

		//init screen
		Screen screen("Venturer - A Choose Your Own Adventure", 1280, 720);
		SDL_Event event;

		//create & load fake bookPage
		bookPage curPage;
		curPage.makeFake();

		//prep text & img (CAN BE MOVED IF WE PASS THE SCREEN TO PAGE.CPP) (simplify it as curPage.draw();)
		screen.prepText(curPage.room_text);
		screen.prepImg(curPage.room_img);

		//plan size of text box (THIS NEEDS TO GO TOO, fix first)
		curPage.imgWidth = 0;
		this->texH = 0;
		SDL_QueryTexture(screen.textTexture, NULL, NULL, &this->texW, &this->texH);
		SDL_Rect dstrect = { 430, 10, this->texW, this->texH };

		//draw loop
		while (!this->quit)
		{
			SDL_WaitEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				this->quit = true;
				break;
			}
			//draw text to screen
			SDL_RenderCopy(screen.renderer, screen.textTexture, NULL, &dstrect);
			SDL_RenderPresent(screen.renderer);
			//draw image to screen
			SDL_Rect dstrect = { 15,173,400,373 };
			SDL_RenderCopy(screen.renderer, screen.imgTexture, NULL, &dstrect);
			SDL_RenderPresent(screen.renderer);
		}

}




























//NEEED:
//IMG_Init(IMG_INIT_PNG);
//IMG_Quit();