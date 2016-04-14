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
		this->hasImg = true;
		//resize vector
		this->choices.resize(2);
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
	void bookPage::load(Screen &screen) {

		//set divider & font size
		this->divider = screen.resY / 36;
		this->txtSize = screen.resY / 45;

		//prep img (if image exists)
		if (this->hasImg == true) {
			//call screen function
			screen.prepImg(this->room_img);
			//get image resolution & ratio
			SDL_QueryTexture(screen.imgTexture, NULL, NULL, &this->imgWidth, &this->imgHeight);
			this->imgXYRatio = (double(this->imgWidth) / double(this->imgHeight));
			//scale image to fill the same screen space
			this->imgWidth = screen.resX / 3.2;
			this->imgHeight = this->imgWidth / this->imgXYRatio;
		}

		// calculate text space (window resX - 3 blank dividers of 20 pixels - imgWidth) - if no image, account for that
		if (this->hasImg == true) {
			this->txtSpace = screen.resX - ((this->divider * 3) + imgWidth);
		}
		else {
			this->txtSpace = screen.resX - (this->divider * 2);
		}

		//prep text
		screen.prepText(this->room_text, this->txtSpace, this->txtSize);

		//get text resolution
		SDL_QueryTexture(screen.txtTexture, NULL, NULL, &this->txtWidth, &this->txtHeight);

		//adjust the placement of the text and image so they are centered
			//determine if there is an image - to account for centering
			if (this->hasImg == true) {
				//calculate text vertical buffer
				this->txtBuffer = ((screen.resY - (this->divider * 2)) - this->txtHeight) / 2;
				//calculate text vertical buffer
				this->imgBuffer = ((screen.resY - (this->divider * 2)) - this->imgHeight) / 2;
				//set text placement
				this->txtRect = { ((this->divider * 2)+ this->imgWidth), this->txtBuffer, this->txtWidth, this->txtHeight };
				//set image placement
				this->imgRect = { this->divider, this->imgBuffer, this->imgWidth, this->imgHeight };
			}
			else {
				//calculate text vertical buffer
				this->txtBuffer = ((screen.resY - (this->divider * 2)) - this->txtHeight) / 2;
				//set text placement
				this->txtRect = { this->txtBuffer, this->divider, this->txtWidth, this->txtHeight };
			}

		//call draw page
		screen.drawPage(this->hasImg,this->txtRect, this->imgRect);

	}