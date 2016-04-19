/*
PAGE.H
This is the header file for the page class
*/

#ifndef PAGE_H
#define PAGE_H

//headers
#include "rapidxml.hpp"
#include "headers/screen.h"
#include <vector>

//--------------------------enums----------------------------//
enum pageType {
	CHOICE,
	CONTINUE,
	DEATH,
	DOOMED,
	NEW_LIFE,
	RETURN_HOME
};
enum pageLayout {
	LEFT,
	RIGHT,
	TOP,
	NONE
};

//-----------------------choice class------------------------//
class Choice
{
public:
	//vars
	int id;
	const char* text;
	const char* past;
	int dest;
	//methods
	Choice(); //constructor
	~Choice(); //destructor
};

//------------------------page class-------------------------//
class Page
{
public:
	//vars
	int id; //page number
	pageType type; //page type
	const char* text; //page text
	const char* img; //page image
	std::vector<Choice> choices; //choice array
	bool hasImg; //image true/false
	pageLayout imgPos; //image position on screen
	//methods
	Page(); //constructor
	~Page(); //destructor
	void makeFake(); //assign demo book page vars
private:
};

//---------------------book class----------------------------//
class Book
{
public:
	//vars
	std::vector<Page> pages; //page array
	//methods
	Book(const char* xmlPath); //constructor
	~Book(); //destructor
	void load(Screen &screen, int pageNum); //load a page 
private:
};

#endif