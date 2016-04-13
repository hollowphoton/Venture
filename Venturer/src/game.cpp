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

//constructor
Game::Game() {

	//init SDL
		//video
		SDL_Init(SDL_INIT_VIDEO);
		//fonts
		TTF_Init();
		//img (png)
		IMG_Init(IMG_INIT_PNG);

	//temp vars for page
	pageTextString = "Could you change history and save hundreds of lives by warning the captain that the \"unsinkable\" Titanic is destined for the bottom of the Atlantic? You see some stairs leading to a higher deck, and you run up them.\n\nA steward is standing near the top. \"You can't come up here,\" he cries. But you dart past him and run toward the forward part of the ship. You dash up another set of stairs, where you find yourself at the starboard wing of the bridge. The gray-bearded captain is standing only a few feet away, looking out to sea through his binoculars at a ship on the horizon.\n\n\"Captain,\" you call out. \"You may not realize it, but this ship will sink in only two or three hours.\"\n\nHe tums and looks at you gravely. \"l know,\" he says softly. \"But we are going to fire distress rockets. That ship out there - the Californian - should respond to help us.\"\n\n\"They will not respond, Captain,\" you tell him. \"They can't believe the Titanic could be in trouble, even though they see your rockets. Your only hope is to put your strongest men in a lifeboat and have them row toward the Californian at top speed - firing rockets as they approach.\"\n\n\"Great heavens, you have bold ideas,\" the captain replies, \"but I need every man I have to lower our lifeboats and keep order among the passengers. I can't believe the Californian will not come when they see our rockets.\"\n\n\"Now go to the deck below. Mr. Lightoller will see that you have a place in a lifeboat.\"\n\nWith that the captain turns and strides away, giving orders to an officer nearby. You sadly return down the stairs and wait in line for one of the places in a lifeboat.\n\nTwo hours later, you sit huddled in the crowded boat, shivering in the cold breeze, and watch the great Titanic slip beneath the waves - with 1,500 people still aboard - together with your only hope of finding your way back to the Cave of Time.";
	pageImgPath = "img/68.bmp";

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

		//prep page text
		SDL_Color color = {190,190,190};
		TTF_Font* gameFont = TTF_OpenFont("fonts/segoeuil.ttf", 16);
		screen.surface = TTF_RenderText_Blended_Wrapped(gameFont, this->pageTextString, color, 840);
		screen.textTexture = SDL_CreateTextureFromSurface(screen.renderer, screen.surface);

		//prep page image
		screen.surface = SDL_LoadBMP(this->pageImgPath);
		screen.imgTexture = SDL_CreateTextureFromSurface(screen.renderer, screen.surface);

		//plan size of text box
		this->texW = 0;
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