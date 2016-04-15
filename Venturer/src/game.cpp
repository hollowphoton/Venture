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

		//init window
			//init screen
			Screen screen("Venturer - A Choose Your Own Adventure", 1600, 900);
			SDL_Event event;
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

		//create/load/draw fake bookPage
		bookPage curPage;
		curPage.makeFake();
		curPage.load(screen);

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

		}

}