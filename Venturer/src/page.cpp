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

//--------------------------------------choice class--------------------------------------//
	//constructor
	Choice::Choice() {
	}

	//destructor
	Choice::~Choice() {
	}
//----------------------------------------------------------------------------------------//

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
		this->type = "choice";
		this->text = "You accept the offer, for you can hardly expect a better life at this point, and soon you begin to enjoy rowing out in the early morning mists and spreading your nets with the neighboring fisherman.\n\nOne afternoon, as the people are pulling up their boats for the night, your friend, Angus McPhee, raises a cry and points at the water. You look out and see the great head and neck of a sea monster - a huge dragon of the lake. Nearby, splinters of wood are floating in the water.\n\n\"That was Sutherland's boat,\" Angus cries out. \"It's been a hundred years since the monster has been seen, but now it has returned!\"\n\nThe monster swims away and soon is lost from view in the mists.\n\n\"How could the monster be gone for a hundred years and then return?\" you ask Angus.\n\n\"Somewhere near Beatty's Point,\" he replies, \"there is an underwater cave where the monster stays as long as it pleases - because it is a Cave of Time.\"\n\nlf only you could find your way back to the Cave of Time! But chances seem slim, and the risks seem great.";
		this->img = "img/54.png";
		this->hasImg = true;
		this->imgPos = "right";
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

//----------------------------------------------------------------------------------------//

//---------------------------------------book class---------------------------------------//
	//constructor
	Book::Book(std::string xmlPath) {

		//use xmlPath to load up this thing                                                                  //WORK ON

	}

	//destructor
	Book::~Book() {
	}

	//load a page
	int Book::load(Screen &screen, int pageNum) {

		//load a page and return the destination that was picked
		screen.drawPage(this->pages[pageNum].hasImg, this->pages[pageNum].imgPos, this->pages[pageNum].img, this->pages[pageNum].text, this->pages[pageNum].choices);

	}
//----------------------------------------------------------------------------------------//