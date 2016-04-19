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
		Screen screen("Venturer - A Choose Your Own Adventure", 1600, 900);
		SDL_Event event;
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

		//create The Cave of Time book from xml
		Book TheCaveOfTime;

		//load up hollow photon logo                                                                //WORK ON

		//load up game intro title                                                                  //WORK ON

		//draw loop
		while (!this->quit)
		{

			//determine state of the game
			switch (TheCaveOfTime.pages[curPage].type)
			{

				//if current page is a choice
				case CHOICE:
					//load up the page
					TheCaveOfTime.load(screen, curPage);
					//wait for next event
					SDL_WaitEvent(&event);
					//event handler
					switch (event.type)
					{

						//if window is forceably closed
						case SDL_QUIT:
							this->quit = true;
							break;

						//if key is pressed
						case SDL_KEYDOWN:
							//check key
							switch (event.key.keysym.sym) {

								//if 1 is pressed and an option for 1 exists
								case SDLK_1:
									//check if option exists
									if (TheCaveOfTime.pages[curPage].choices.size() >= 1) {
										//set new curPage
										curPage = TheCaveOfTime.pages[curPage].choices[0].dest;
									}
									break;

								//if 2 is pressed and an option for 2 exists
								case SDLK_2:
									//check if option exists
									if (TheCaveOfTime.pages[curPage].choices.size() >= 2) {
										//set new curPage
										curPage = TheCaveOfTime.pages[curPage].choices[1].dest;
									}
									break;

								//if 3 is pressed and an option for 3 exists
								case SDLK_3:
									//check if option exists
									if (TheCaveOfTime.pages[curPage].choices.size() >= 3) {
										//set new curPage
										curPage = TheCaveOfTime.pages[curPage].choices[2].dest;
									}
									break;

								//if 4 is pressed and an option for 4 exists
								case SDLK_4:
									//check if option exists
									if (TheCaveOfTime.pages[curPage].choices.size() >= 4) {
										//set new curPage
										curPage = TheCaveOfTime.pages[curPage].choices[3].dest;
									}
									break;

							//break from key detect
							}
							break;

					}
					break;

				//if current page is a continue
				case CONTINUE:
					//load up the page
					TheCaveOfTime.load(screen, curPage);
					//wait for next event
					SDL_WaitEvent(&event);
					//event handler
					switch (event.type)
					{

						//if window is forceably closed
						case SDL_QUIT:
							this->quit = true;
							break;

						//if key is pressed
						case SDL_KEYDOWN:
							//check key
							switch (event.key.keysym.sym) {

								//if Enter key is pressed
								case SDLK_RETURN:
									//set new curPage
									curPage = TheCaveOfTime.pages[curPage].choices[0].dest;
									break;

							}
							break;

					}
					break;

				//if current page is a doomed, death, new life, or return home (default)
				default:
					//we stop the loop here
					TheCaveOfTime.load(screen, curPage);
					//wait for next event
					SDL_WaitEvent(&event);
					//event handler
					switch (event.type)
					{
						//if window is forceably closed
					case SDL_QUIT:
						this->quit = true;
						break;
					}
					break;
			}

		}

	}