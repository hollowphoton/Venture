/*
PAGE CLASS
This class controls the displaying of book pages, including:
-page text
-choices
-picking where to go next
-ending the game
*/

//headers
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "headers/page.h"
#include "headers/screen.h"
#include <string>
#include <map>

//--------------------------------------choice class--------------------------------------//
	//constructor
	Choice::Choice() {
	}

	//destructor
	Choice::~Choice() {
	}

//---------------------------------------page class---------------------------------------//
	//constructor
	Page::Page() {
	}

	//destructor
	Page::~Page() {
	}

//---------------------------------------book class---------------------------------------//
	//constructor
	Book::Book() : bFile("xml/the_cave_of_time.xml") {

		//init vars

		int pageCount = 0;
		int curPage = 0;
		int choiceCount = 0;
		int curChoice = 0;

		//create ENUM dictionaries
			//pageType
			std::map< std::string, pageType > PTdict;
			PTdict["CHOICE"] = CHOICE;
			PTdict["CONTINUE"] = CONTINUE;
			PTdict["DEATH"] = DEATH;
			PTdict["DOOMED"] = DOOMED;
			PTdict["NEW_LIFE"] = NEW_LIFE;
			PTdict["RETURN_HOME"] = RETURN_HOME;
			//imageLayout
			std::map< std::string, imageLayout > ILdict;
			ILdict["LEFT"] = LEFT;
			ILdict["RIGHT"] = RIGHT;
			ILdict["TOP"] = TOP;
			ILdict["NONE"] = NONE;

		//parse xml
		this->bDoc.parse<0>(this->bFile.data());

		//find root node
		rapidxml::xml_node<>* book_node = this->bDoc.first_node("book");

		//set book size
			//find out book size
			for (rapidxml::xml_node<>* page_node = book_node->first_node("page"); page_node; page_node = page_node->next_sibling())
			{
				pageCount++;
			}
			//set page vector size to # of pages in xml
			this->pages.resize(pageCount);

		//iterate over the pages and grab contents
		for (rapidxml::xml_node<>* page_node = book_node->first_node("page"); page_node; page_node = page_node->next_sibling())
		{
			//set current page number
			curPage = atoi(page_node->first_attribute("number")->value());

			//set vars for current page
			this->pages[curPage].id = atoi(page_node->first_attribute("number")->value());
			this->pages[curPage].type = PTdict[page_node->first_node("type")->value()];
			this->pages[curPage].text = page_node->first_node("text")->value();
			this->pages[curPage].img = page_node->first_node("image")->value();
			if(strcmp(page_node->first_node("image")->value(),"null") == 0){
				this->pages[curPage].hasImg = false;
			}
			else {
				this->pages[curPage].hasImg = true;
			}
			this->pages[curPage].imgPos = ILdict[page_node->first_node("imagePos")->value()];

			//do we have choices?
			if (page_node->first_node("choice") != 0) {

				//set choice size
					//find out choice size
				for (rapidxml::xml_node<> * choice_node = page_node->first_node("choice"); choice_node; choice_node = choice_node->next_sibling())
				{
					choiceCount++;
				}
				//set choice vector size to # of pages in xml
				this->pages[curPage].choices.resize(choiceCount);
				//reset choice counter
				choiceCount = 0;

				//iterate over the choices and grab contents
				for (rapidxml::xml_node<> * choice_node = page_node->first_node("choice"); choice_node; choice_node = choice_node->next_sibling())
				{
					//set current choice number
					curChoice = atoi(choice_node->first_attribute("number")->value())-1;

					//set vars for current page
					this->pages[curPage].choices[curChoice].id = atoi(choice_node->first_attribute("number")->value());
					this->pages[curPage].choices[curChoice].text = choice_node->first_node("text")->value();
					this->pages[curPage].choices[curChoice].past = choice_node->first_node("past")->value();
					this->pages[curPage].choices[curChoice].dest = atoi(choice_node->first_node("room_dest")->value());
				}

			}

		}

	}

	//destructor
	Book::~Book() {
	}

	//load a page
	void Book::load(Screen &screen, int pageNum) {

		//load a page and return the destination that was picked
		screen.drawPage(this->pages[pageNum].hasImg, this->pages[pageNum].imgPos, this->pages[pageNum].type, this->pages[pageNum].img, this->pages[pageNum].text, this->pages[pageNum].choices);

	}