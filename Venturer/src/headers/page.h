/*
PAGE.H
This is the header file for the page class
*/

#ifndef PAGE_H
#define PAGE_H

//headers
#include "rapidxml.hpp"
#include "headers/screen.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//page choice class
class pageChoice
{
public:
	//vars
	int choice_id = 0;
	std::string choice_text;
	std::string choice_past;
	int room_dest = 0;
	//methods
	pageChoice(); //constructor
	~pageChoice(); //destructor
private:
};

//book page class
class bookPage
{
public:
	//vars
	int room_id = 0; //page number
	std::string room_type; //page type
	const char* room_text; //page text
	const char* room_img; //page image
	std::vector<pageChoice> choices; //choice array
	bool hasImg; //image true/false
	SDL_Rect txtRect; //final text coordinates
	SDL_Rect imgRect; //final image coordinates
	//methods
	bookPage(); //constructor
	~bookPage(); //destructor
	void makeFake(); //assign demo book page vars
	void load(Screen &screen); //load the page 
private:
};

#endif