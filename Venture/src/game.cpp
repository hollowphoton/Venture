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

		//load up game intro
		TheCaveOfTime.drawIntro(screen);

		//load up game title
		//TheCaveOfTime.drawTitle(screen, "img/Title.png", 4); //<----------------------------------------------REDO

		//load up game warning
		//TheCaveOfTime.load(screen, curPage);                 //<----------------------------------------------REDO

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
			switch (event.type)                              //<----------------------------------------------REDO
			{

				//check for quit (all page types)
				case SDL_QUIT:
					this->quit = true;
					break;

				////if key is pressed
				//case SDL_KEYDOWN:
				//	//check key
				//	switch (event.key.keysym.sym) {
				//		case SDLK_1:
				//			//check if this is a choice
				//			if (TheCaveOfTime.pages[curPage].type == CHOICE) {           //<----------------------------------------------REDO
				//				//set curPage
				//				curPage = TheCaveOfTime.pages[curPage].choices[0].dest;           //<----------------------------------------------REDO
				//				//load new page
				//				TheCaveOfTime.load(screen, curPage);           //<----------------------------------------------REDO
				//			}
				//			//break
				//			break;
				//		case SDLK_2:
				//			//check if this is a choice
				//			if (TheCaveOfTime.pages[curPage].type == CHOICE) {           //<----------------------------------------------REDO
				//				//set curPage
				//				curPage = TheCaveOfTime.pages[curPage].choices[1].dest;           //<----------------------------------------------REDO
				//				//load new page
				//				TheCaveOfTime.load(screen, curPage);           //<----------------------------------------------REDO
				//			}
				//			//break
				//			break;
				//		case SDLK_3:
				//			//check if this is a choice
				//			if (TheCaveOfTime.pages[curPage].type == CHOICE) {           //<----------------------------------------------REDO
				//				//set curPage
				//				curPage = TheCaveOfTime.pages[curPage].choices[2].dest;           //<----------------------------------------------REDO
				//				//load new page
				//				TheCaveOfTime.load(screen, curPage);           //<----------------------------------------------REDO
				//			}
				//			//break
				//			break;
				//		case SDLK_4:
				//			//check if this is a choice
				//			if (TheCaveOfTime.pages[curPage].type == CHOICE) {           //<----------------------------------------------REDO
				//				//set curPage
				//				curPage = TheCaveOfTime.pages[curPage].choices[3].dest;           //<----------------------------------------------REDO
				//				//load new page
				//				TheCaveOfTime.load(screen, curPage);           //<----------------------------------------------REDO
				//			}
				//			//break
				//			break;
				//		case SDLK_RETURN:
				//			//check if this is a continue
				//			if (TheCaveOfTime.pages[curPage].type == CONTINUE) {           //<----------------------------------------------REDO
				//				//set curPage
				//				curPage = TheCaveOfTime.pages[curPage].choices[0].dest;           //<----------------------------------------------REDO
				//				//load new page
				//				TheCaveOfTime.load(screen, curPage);           //<----------------------------------------------REDO
				//			}
				//			//break
				//			break;
				//	}
				//	//break
				//	break;

			}

		}

	}