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
			Screen screen("Venturer - A Choose Your Own Adventure", 1920, 1080);
			SDL_Event event;
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

		//create The Cave of Time book from xml
		Book TheCaveOfTime("/xml/the_cave_of_time.xml");

		//load up hollow photon logo                                                                //WORK ON

		//load up game intro title                                                                //WORK ON

		//load up the first page
		TheCaveOfTime.load(screen, 0);

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