/*
PAGE.H
This is the header file for the page class
*/

#ifndef BOOK_H
#define BOOK_H

//headers
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "headers/global.h"
#include <vector>
#include <map>

//forward includes
class Screen;


//-----------------------pageType struct------------------------//
struct pageType
{
	std::string type;
	std::string name;
	const char* text;
	std::string textFormat;
	std::string hAlign;
	std::string musicPath;
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
	int id;
	std::string type;
	const char* text;
	std::string itemType;
	const char* item;
	double itemScaleY;
	double itemX;
	double itemY;
	double textScaleX;
	double textX;
	double textY;
	std::vector<Choice> choices;
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
	int id;
	const char* title;
	std::string name;
	const char* author;
	const char* illustrator;
	const char* titleImgPath;
	const char* coverImgPath;
	std::map<std::string, pageType> pageFormat;
	//methods
	Book(const char* xmlPath); //constructor
	~Book(); //destructor
	void drawTitlePage(Screen &screen); //draw the book title
	void drawLogo(Screen &screen, const char* logoPath); //load a logo
	void drawPage(Screen &screen, int pageNum); //draw the page
private:
	rapidxml::file<> bFile;
	rapidxml::xml_document<> bDoc;
};

#endif