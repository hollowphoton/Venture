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
	std::string text;
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
	std::string text;
	std::string past;
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
	std::string text;
	std::string itemType;
	std::string item;
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
	std::string title;
	std::string name;
	std::string author;
	std::string illustrator;
	std::string titleImgPath;
	std::string coverImgPath;
	std::map<std::string, pageType> pageFormat;
	//methods
	Book(const char* xmlPath); //constructor
	~Book(); //destructor
	//void load(Screen &screen, int pageNum); //load a page                 //<----------------------------------------------REDO
	//void drawTitle(Screen &screen, const char* imgPath, int waitTime); //load book title                 //<----------------------------------------------REDO
private:
	rapidxml::file<> bFile;
	rapidxml::xml_document<> bDoc;
};

#endif