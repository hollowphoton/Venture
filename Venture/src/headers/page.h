/*
PAGE.H
This is the header file for the page class
*/

#ifndef PAGE_H
#define PAGE_H

//headers
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "headers/global.h"
#include <vector>

//forward includes
class Screen;

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
	imageLayout imgPos; //image position on screen
	//methods
	Page(); //constructor
	~Page(); //destructor
private:
};

//---------------------book class----------------------------//
class Book
{
public:
	//vars
	std::vector<Page> pages; //page array
	//methods
	Book(); //constructor
	~Book(); //destructor
	void load(Screen &screen, int pageNum); //load a page 
private:
	rapidxml::file<> bFile;
	rapidxml::xml_document<> bDoc;
};

#endif