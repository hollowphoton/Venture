/*
PAGE CLASS
This class controls the displaying of book pages, including:
-page text
-choices
-picking where to go next
-ending the game
*/

//headers
#include "headers/page.h"
#include <fstream>
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

	//assign demo book page vars
	void Page::makeFake() {
		//assign page vars
		this->id = 54;
		this->type = CHOICE;
		this->text = "You accept the offer, for you can hardly expect a better life at this point, and soon you begin to enjoy rowing out in the early morning mists and spreading your nets with the neighboring fisherman.\n\nOne afternoon, as the people are pulling up their boats for the night, your friend, Angus McPhee, raises a cry and points at the water. You look out and see the great head and neck of a sea monster - a huge dragon of the lake. Nearby, splinters of wood are floating in the water.\n\n\"That was Sutherland's boat,\" Angus cries out. \"It's been a hundred years since the monster has been seen, but now it has returned!\"\n\nThe monster swims away and soon is lost from view in the mists.\n\n\"How could the monster be gone for a hundred years and then return?\" you ask Angus.\n\n\"Somewhere near Beatty's Point,\" he replies, \"there is an underwater cave where the monster stays as long as it pleases - because it is a Cave of Time.\"\n\nlf only you could find your way back to the Cave of Time! But chances seem slim, and the risks seem great.";
		this->img = "img/54.png";
		this->hasImg = true;
		this->imgPos = RIGHT;
		//resize vector
		this->choices.resize(2);
		//assign choice 1
		this->choices[0].id = 1;
		this->choices[0].text = "Try";
		this->choices[0].past = "You try.";
		this->choices[0].dest = 57;
		//assign choice 2
		this->choices[1].id = 2;
		this->choices[1].text = "Do not try";
		this->choices[1].past = "You do not try.";
		this->choices[1].dest = 60;
	}

//---------------------------------------book class---------------------------------------//
	//constructor
	Book::Book(const char* xmlPath) {

		//init vars
		rapidxml::xml_document<> doc;
		rapidxml::xml_node<> * root_node;
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
			//pageLayout
			std::map< std::string, pageLayout > PLdict;
			PLdict["LEFT"] = LEFT;
			PLdict["RIGHT"] = RIGHT;
			PLdict["TOP"] = TOP;
			PLdict["NONE"] = NONE;

		//read the xml file into a vector
		std::ifstream theFile(xmlPath);
		std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		//parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);

		//find root node
		root_node = doc.first_node("book");

		//set book size
			//find out book size
			for (rapidxml::xml_node<> * page_node = root_node->first_node("page"); page_node; page_node = page_node->next_sibling())
			{
				pageCount++;
			}
			//set page vector size to # of pages in xml
			this->pages.resize(pageCount);

		//iterate over the pages and grab contents
		for (rapidxml::xml_node<> * page_node = root_node->first_node("page"); page_node; page_node = page_node->next_sibling())
		{
			//set current page number
			curPage = int(page_node->first_attribute("number")->value());

			//set vars for current page
			this->pages[curPage].id = int(page_node->first_attribute("number")->value());
			this->pages[curPage].type = PTdict[page_node->first_node("type")->value()];
			this->pages[curPage].text = page_node->first_node("text")->value();
			this->pages[curPage].img = page_node->first_node("image")->value();
			if(page_node->first_node("image")->value()=="null"){
				this->pages[curPage].hasImg = false;
			}
			else {
				this->pages[curPage].hasImg = true;
			}
			this->pages[curPage].imgPos = PLdict[page_node->first_node("imagePos")->value()];

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
					curChoice = int(choice_node->first_attribute("number")->value());

					//set vars for current page
					this->pages[curPage].choices[curChoice].id = int(page_node->first_attribute("number")->value());
					this->pages[curPage].choices[curChoice].text = choice_node->first_node("text")->value();
					this->pages[curPage].choices[curChoice].past = choice_node->first_node("past")->value();
					this->pages[curPage].choices[curChoice].dest = int(choice_node->first_node("room_dest")->value());
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