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

		//init vars
		int imgWidth; //image size x
		int imgHeight; //image size y
		int imgBuffer; //img vertical buffer
		double imgXYRatio; //img x/y ratio
		int txtSize; //txt font size
		int divider; //pixel size of divider between all screen elements
		int txtWidth; //text pixel width
		int txtHeight; //text pixel height
		int txtBuffer; //text vertical buffer
		int txtSpace; //allotted space that fits text

		//set divider & font size
		divider = screen.resY / 36;
		txtSize = screen.resY / 45;

		//prep img (if image exists)
		if (this->hasImg == true) {
			//call screen function
			screen.prepImg(this->room_img);
			//get image resolution & ratio
			SDL_QueryTexture(screen.imgTexture, NULL, NULL, &imgWidth, &imgHeight);
			imgXYRatio = (double(imgWidth) / double(imgHeight));
			//scale image to fill the same screen space
			imgWidth = int(screen.resX / 3.2);
			imgHeight = int(imgWidth / imgXYRatio);
		}

		// calculate text space (window resX - 3 blank dividers of 20 pixels - imgWidth) - if no image, account for that
		if (this->hasImg == true) {
			txtSpace = screen.resX - ((divider * 3) + imgWidth);
		}
		else {
			txtSpace = screen.resX - (divider * 2);
		}

		//prep text
		screen.prepText(this->room_text, txtSpace, txtSize);

		//get text resolution
		SDL_QueryTexture(screen.txtTexture, NULL, NULL, &txtWidth, &txtHeight);

		//adjust the placement of the text and image so they are centered
			//determine if there is an image - to account for centering
			if (this->hasImg == true) {
				//calculate text vertical buffer
				txtBuffer = ((screen.resY - (divider * 2)) - txtHeight) / 2;
				//calculate text vertical buffer
				imgBuffer = ((screen.resY - (divider * 2)) - imgHeight) / 2;
				//set text placement
				this->txtRect = { ((divider * 2)+ imgWidth), txtBuffer, txtWidth, txtHeight };
				//set image placement
				this->imgRect = { divider, imgBuffer, imgWidth, imgHeight };
			}
			else {
				//calculate text vertical buffer
				txtBuffer = ((screen.resY - (divider * 2)) - txtHeight) / 2;
				//set text placement
				this->txtRect = { txtBuffer, divider, txtWidth, txtHeight };
			}

		//call draw page
		screen.drawPage(this->hasImg,this->txtRect, this->imgRect);

	}