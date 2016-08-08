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

//---------------------------------------game methods--------------------------------------//
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
		this->bookLoop();

	}

	//destructor
	Game::~Game() {
	}

	//game loop
	void Game::bookLoop() {

		//init vars
		int curPage = 0;

		//init window & settings
		Screen screen("VENTURE", 1600, 900);
		SDL_Event event;
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

		//create The Cave of Time book from xml
		Book TheCaveOfTime("xml/1_tcot.xml");

		//load up company logo
		TheCaveOfTime.drawLogo(screen, "img/hollow_photon_logo.png");

		//load up game title
		TheCaveOfTime.drawLogo(screen, "img/venture_logo_small.png");

		//load up book title
		TheCaveOfTime.drawTitlePage(screen);
		
		//load up first page
		TheCaveOfTime.drawPage(screen, curPage);

		//draw loop
		while (!this->quit)
		{

			////---------DEBUG MODE ONLY - LOOP THROUGH ALL PAGES - REMOVE COMMENTS TO TURN ON--------//
			//for (int i = 0; i < 96; i++) {
			//	//load up the page
			//	TheCaveOfTime.drawPage(screen, i);
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
					//check if 1 is pressed
					if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP_1) {
						//check if this is a choice
						if (TheCaveOfTime.pages[curPage].type == "CHOICE") {
							//set curPage
							curPage = TheCaveOfTime.pages[curPage].choices[0].dest;
							//load new page
							TheCaveOfTime.drawPage(screen, curPage);
						}
						//get out of the switch
						break;
					}
					//check if 2 is pressed
					if (event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_2) {
						//check if this is a choice
						if (TheCaveOfTime.pages[curPage].type == "CHOICE") {
							//set curPage
							curPage = TheCaveOfTime.pages[curPage].choices[1].dest;
							//load new page
							TheCaveOfTime.drawPage(screen, curPage);
						}
						//get out of the switch
						break;
					}
					//check if 3 is pressed
					if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP_3) {
						//check if this is a choice
						if (TheCaveOfTime.pages[curPage].type == "CHOICE") {
							//set curPage
							curPage = TheCaveOfTime.pages[curPage].choices[2].dest;
							//load new page
							TheCaveOfTime.drawPage(screen, curPage);
						}
						//get out of the switch
						break;
					}
					//check if 4 is pressed
					if (event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP_4) {
						//check if this is a choice
						if (TheCaveOfTime.pages[curPage].type == "CHOICE") {
							//set curPage
							curPage = TheCaveOfTime.pages[curPage].choices[3].dest;
							//load new page
							TheCaveOfTime.drawPage(screen, curPage);
						}
						//get out of the switch
						break;
					}
					//check if this is a continue (ANY KEY)
					if (TheCaveOfTime.pages[curPage].type == "CONTINUE") {
						//set curPage
						curPage = TheCaveOfTime.pages[curPage].choices[0].dest;
						//load new page
						TheCaveOfTime.drawPage(screen, curPage);
					}
						
				//break
				break;

			}

		}

	}