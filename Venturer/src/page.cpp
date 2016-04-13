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

//pageChoice

	//constructor
	pageChoice::pageChoice() {
	}

	//destructor
	pageChoice::~pageChoice() {
	}

//bookPage

	//constructor
	bookPage::bookPage() {
	}

	//destructor
	bookPage::~bookPage() {
	}

	//assign demo book page vars
	void bookPage::makeFake() {
		//assign page vars
		this->room_id = 11;
		this->room_type = "choice";
		this->room_text = "\"Off to the tower,\" the King shouts. Two knights leap forward, drag you out of the chamber, and, with spears at your back, force you to climb forty-eight stone steps to the tower prison - a tiny cylindrical room with one small window looking out over the moat and pasture land beyond. The only furniture is a bed of straw.\n\nYou realize you are back in the early days of feudal Europe, where the only laws are the King's whims. You have no idea how long he intends to keep you in the tower. There is one possibility of escape. The water in the moat, about twenty-five feet almost directly below your window, is quite deep. If you jump out far enough, you should land in the deep water and not be hurt.";
		this->room_img = "img/11.png";
		//assign choice 1
		this->choices[0].choice_id = 1;
		this->choices[0].choice_text = "Jump";
		this->choices[0].choice_past = "You jump.";
		this->choices[0].room_dest = 12;
		//assign choice 2
		this->choices[1].choice_id = 2;
		this->choices[1].choice_text = "Stay put";
		this->choices[1].choice_past = "You stay put.";
		this->choices[1].room_dest = 13;
	}

	//load
	void bookPage::load() {
		//prep text
		prepText(this->room_text);
		//prep img
		prepImg(this->room_img);
		//draw
	}