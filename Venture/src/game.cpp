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
#include "headers/global.h"

//---------------------------------------page class--------------------------------------//
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

		//init vars
		int curPage = 0;

		//init window & settings
		Screen screen("Venturer - A Choose Your Own Adventure", 1920, 1080);
		SDL_Event event;
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

		//create The Cave of Time book from xml
		Book TheCaveOfTime;

		//draw game titles
			//draw hollow photon title
			screen.drawTitle("image", "img/hollow_photon_logo.png", "x", 2);
			//draw venture title
			screen.drawTitle("image", "img/venture_logo_small.png", "x", 3);
			//draw cave of time title
			screen.drawTitle("image", "img/Title.png", "x", 4);
			//draw game intro text
			screen.drawTitle("text", "x", "This game contains many different adventures you can go on in the Cave of Time. From time to time as you read along, you will be asked to make a choice. Your choice may lead to success or disaster.\n\nThe adventures you take are a result of your choice. You are responsible because you choose!\n\nThink carefully before you make a move! One mistake can be your last . . . or it may lead you to fame and fortune!", 10);

		//load up first page
		TheCaveOfTime.load(screen, curPage);

		//draw loop
		while (!this->quit)
		{



			////---------DEBUG MODE ONLY - LOOP THROUGH ALL PAGES - REMOVE COMMENTS TO TURN ON--------//
			//for (int i = 0; i < 96; i++) {
			//	//load up the page
			//	TheCaveOfTime.load(screen, i);
			//	//wait for next event
			//	SDL_Delay(1000);
			//}
			//this->quit = true;
			////--------------------------------------------------------------------------------------//




			//wait for next event
			SDL_WaitEvent(&event);
			//event handler
			switch (event.type)
			{

				//check for quit (all page types)
				case SDL_QUIT:
					this->quit = true;
					break;

				//if key is pressed
				case SDL_KEYDOWN:
					//check key
					switch (event.key.keysym.sym) {
						case SDLK_1:
							//check if this is a choice
							if (TheCaveOfTime.pages[curPage].type == CHOICE) {
								//set curPage
								curPage = TheCaveOfTime.pages[curPage].choices[0].dest;
								//load new page
								TheCaveOfTime.load(screen, curPage);
							}
							//break
							break;
						case SDLK_2:
							//check if this is a choice
							if (TheCaveOfTime.pages[curPage].type == CHOICE) {
								//set curPage
								curPage = TheCaveOfTime.pages[curPage].choices[1].dest;
								//load new page
								TheCaveOfTime.load(screen, curPage);
							}
							//break
							break;
						case SDLK_3:
							//check if this is a choice
							if (TheCaveOfTime.pages[curPage].type == CHOICE) {
								//set curPage
								curPage = TheCaveOfTime.pages[curPage].choices[2].dest;
								//load new page
								TheCaveOfTime.load(screen, curPage);
							}
							//break
							break;
						case SDLK_4:
							//check if this is a choice
							if (TheCaveOfTime.pages[curPage].type == CHOICE) {
								//set curPage
								curPage = TheCaveOfTime.pages[curPage].choices[3].dest;
								//load new page
								TheCaveOfTime.load(screen, curPage);
							}
							//break
							break;
						case SDLK_RETURN:
							//check if this is a continue
							if (TheCaveOfTime.pages[curPage].type == CONTINUE) {
								//set curPage
								curPage = TheCaveOfTime.pages[curPage].choices[0].dest;
								//load new page
								TheCaveOfTime.load(screen, curPage);
							}
							//break
							break;
					}
					//break
					break;

			}

		}

	}