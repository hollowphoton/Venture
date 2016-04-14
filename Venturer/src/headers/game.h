/*
GAME.H
This is the header file for the game class
*/


#ifndef GAME_H
#define GAME_H

//headers
#include "headers/screen.h"

//game loop class
class Game
{
public:
	//vars
	bool quit = false;

	//methods
	Game(); //constructor
	~Game(); //destructor
	void gameLoop(); //main game loop
private:
};

#endif