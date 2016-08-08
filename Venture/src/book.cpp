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
#include "headers/book.h"
#include "headers/screen.h"
#include <string>


//--------------------------------------choice methods--------------------------------------//
	//constructor
	Choice::Choice() {
	}

	//destructor
	Choice::~Choice() {
	}

//---------------------------------------page methods---------------------------------------//
	//constructor
	Page::Page() {
	}

	//destructor
	Page::~Page() {
	}

//---------------------------------------book methods---------------------------------------//
	//constructor
	Book::Book(const char* xmlPath) : bFile(xmlPath) {

		//init vars

		int pageCount = 0;
		int curPage = 0;
		int choiceCount = 0;
		int curChoice = 0;
		pageType curPT;

		//parse xml
		this->bDoc.parse<0>(this->bFile.data());

		//find root node
		rapidxml::xml_node<>* book_node = this->bDoc.first_node("book");
		
		//ingest book data
			//set book number
			this->id = atoi(book_node->first_attribute("number")->value());
			//find contents node
			rapidxml::xml_node<>* contents_node = book_node->first_node("contents");
			//set main book attributes
			this->title = contents_node->first_node("title")->value();
			this->name = contents_node->first_node("name")->value();
			this->author = contents_node->first_node("author")->value();
			this->illustrator = contents_node->first_node("illustrator")->value();
			this->titleImgPath = contents_node->first_node("titleImgPath")->value();
			this->coverImgPath = contents_node->first_node("coverImgPath")->value();
			//ingest pageTypes into map
			for (rapidxml::xml_node<> * pageType_node = contents_node->first_node("pageType"); pageType_node; pageType_node = pageType_node->next_sibling())
			{
				//ingest this pageType into the temp pageType
				curPT.type = pageType_node->first_node("type")->value();
				curPT.name = pageType_node->first_node("name")->value();
				curPT.text = pageType_node->first_node("text")->value();
				curPT.textFormat = pageType_node->first_node("textFormat")->value();
				curPT.hAlign = pageType_node->first_node("hAlign")->value();
				curPT.musicPath = pageType_node->first_node("musicPath")->value();
				//insert entry into map for this pageType
				this->pageFormat[pageType_node->first_node("label")->value()] = curPT;
			}

		//ingest book data
			//identify number of pages
			for (rapidxml::xml_node<>* page_node = book_node->first_node("page"); page_node; page_node = page_node->next_sibling())
			{
				pageCount++;
			}
			//set page vector size to # of pages in xml
			this->pages.resize(pageCount);
			//iterate over the pages and grab page data
			for (rapidxml::xml_node<>* page_node = book_node->first_node("page"); page_node; page_node = page_node->next_sibling())
			{
				//set current page number
				curPage = atoi(page_node->first_attribute("number")->value());
				//set vars for current page
				this->pages[curPage].id = atoi(page_node->first_attribute("number")->value());
				this->pages[curPage].type = page_node->first_node("type")->value();
				this->pages[curPage].text = page_node->first_node("text")->value();
				this->pages[curPage].itemType = page_node->first_node("itemType")->value();
				this->pages[curPage].item = page_node->first_node("item")->value();
				this->pages[curPage].itemScaleY = atof(page_node->first_node("itemScaleY")->value());
				this->pages[curPage].itemX = atof(page_node->first_node("itemX")->value());
				this->pages[curPage].itemY = atof(page_node->first_node("itemY")->value());
				this->pages[curPage].textScaleX = atof(page_node->first_node("textScaleX")->value());
				this->pages[curPage].textX = atof(page_node->first_node("textX")->value());
				this->pages[curPage].textY = atof(page_node->first_node("textY")->value());
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
						this->pages[curPage].choices[curChoice].dest = atoi(choice_node->first_node("dest")->value());
					}
				}
			}

	}

	//destructor
	Book::~Book() {
	}

	//draw book intro screen
	void Book::drawLogo(Screen &screen, const char* logoPath) {

		//clean screen
		screen.cleanScreen();

		//init vars
		int textureWidth, textureHeight, imgSizeX, imgSizeY, destX, destY;
		SDL_Rect destRect;

		//set vars
		imgSizeX = int(screen.resX / 1.5);

		//draw logo to buffer
		//draw image to texture
		screen.makeImageTexture(logoPath);
		//get dimensions
		SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
		//set x size of image
		imgSizeY = int(textureHeight * (double(imgSizeX) / double(textureWidth)));
		//set destination
		destX = (screen.resX - imgSizeX) / 2;
		destY = (screen.resY - imgSizeY) / 2;
		destRect = { destX, destY, imgSizeX, imgSizeY };
		//draw texture to buffer
		screen.drawTexture(screen.texture, destRect);

		//render buffer to screen
		screen.renderBuffer();

		//title hold time
		SDL_Delay(3000);

	}

	//draw book title 
	void Book::drawTitlePage(Screen &screen) {

		//clean screen
		screen.cleanScreen();
		
		//init vars
		int textureWidth, textureHeight, yBufferSize, imgSizeX, imgSizeY, titleFontSize, authFontSize, illusFontSize, titleFontGap, authFontGap, illusFontGap, maxWidth, destX, destY;
		SDL_Rect destRect;

		//set vars
		yBufferSize = screen.resY / 60;
		imgSizeY = int(screen.resY / 2);
		titleFontSize = int(screen.resY / 14);
		authFontSize = int(screen.resY / 30);
		illusFontSize = int(screen.resY / 45);
		maxWidth = screen.resX;

		//sample font vertical sizes
			//title
			titleFontGap = int(TTF_FontLineSkip(TTF_OpenFont("fonts/benguiat_bold.ttf", titleFontSize)) * .79);
			//author
			authFontGap = int(TTF_FontLineSkip(TTF_OpenFont("fonts/benguiat_bold.ttf", authFontSize)) * .79);
			//illustrator
			illusFontGap = int(TTF_FontLineSkip(TTF_OpenFont("fonts/benguiat_bold.ttf", illusFontSize)) * .79);

		//draw title page to buffer
			//book title
				//draw text to texture
				screen.makeTextTexture("fonts/benguiat_bold.ttf", titleFontSize, this->title, { 0,0,0 }, maxWidth);
				//get dimensions
				SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
				//set destination
				destX = (screen.resX - textureWidth) / 2;
				destY = (screen.resY - (titleFontGap + authFontGap + imgSizeY + illusFontGap + (yBufferSize * 3))) / 2;
				destRect = { destX, destY, textureWidth, textureHeight };
				//draw texture to buffer
				screen.drawTexture(screen.texture, destRect);
			//author
				//draw text to texture
				screen.makeTextTexture("fonts/benguiat_bold.ttf", authFontSize, this->author, { 0,0,0 }, maxWidth);
				//get dimensions
				SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
				//set destination
				destX = (screen.resX - textureWidth) / 2;
				destY = destY + (titleFontGap + yBufferSize);
				destRect = { destX, destY, textureWidth, textureHeight };
				//draw texture to buffer
				screen.drawTexture(screen.texture, destRect);
			//title image
				//draw image to texture
				screen.makeImageTexture(this->titleImgPath);
				//get dimensions
				SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
				//set x size of image
				imgSizeX = int(textureWidth * (double(imgSizeY) / double(textureHeight)));
				//set destination
				destX = (screen.resX - imgSizeX) / 2;
				destY = destY + (authFontGap + yBufferSize);
				destRect = { destX, destY, imgSizeX, imgSizeY };
				//draw texture to buffer
				screen.drawTexture(screen.texture, destRect);
			//line below the title (uses title image width)
				//draw line
				SDL_Rect fillRect = { destX, ((screen.resY - (titleFontGap + authFontGap + imgSizeY + illusFontGap + (yBufferSize * 3))) / 2) + titleFontGap + ((yBufferSize - screen.resY / 200) / 2), imgSizeX, (screen.resY / 200) };
				SDL_SetRenderDrawColor(screen.renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderFillRect(screen.renderer, &fillRect);
			//illustrator
				//draw text to texture
				screen.makeTextTexture("fonts/benguiat_bold.ttf", illusFontSize, this->illustrator, { 0,0,0 }, maxWidth);
				//get dimensions
				SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
				//set destination
				destX = (screen.resX - textureWidth) / 2;
				destY = destY + (imgSizeY + yBufferSize);
				destRect = { destX, destY, textureWidth, textureHeight };
				//draw texture to buffer
				screen.drawTexture(screen.texture, destRect);

		//render buffer to screen
				screen.renderBuffer();

		//title hold time
		SDL_Delay(5000);

	}

	//prep page
	void Book::drawPage(Screen &screen, int pageNum) {

		//clean screen
		screen.cleanScreen();

		//init vars
		int textureWidth, textureHeight, txtSize, imgSizeX, imgSizeY, destX, destY, textFontSize, warningFontSize, textWidth, textFontGap, endTextSize, endMarkerX, endMarkerY;
		SDL_Rect destRect;

		//set vars
		textFontSize = int(screen.resY / 35);
		warningFontSize = int(screen.resY / 12);
		textWidth = screen.resX * this->pages[pageNum].textScaleX;

		//sample font vertical size of choice and page end text
		textFontGap = int(TTF_FontLineSkip(TTF_OpenFont("fonts/benguiat_bold.ttf", textFontSize)) * .79);

		//draw warning (if warning exists)
		if (this->pages[pageNum].itemType == "WARNING") {
			//draw text to texture
			screen.makeTextTexture("fonts/souvenir.ttf", warningFontSize, this->pages[pageNum].item, { 0,0,0 }, (screen.resX / 2));
			//get dimensions
			SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
			//calc text destination
			destX = (screen.resX * this->pages[pageNum].itemX) - (textureWidth / 2);
			destY = (screen.resY * this->pages[pageNum].itemY) - (textureHeight / 2);
			//set destination
			destRect = { destX, destY, textureWidth, textureHeight };
			//draw texture to buffer
			screen.drawTexture(screen.texture, destRect);
		}

		//draw image (if image exists)
		if (this->pages[pageNum].itemType == "IMAGE") {
			//draw image to texture
			screen.makeImageTexture(this->pages[pageNum].item);
			//get dimensions
			SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
			//calc scaled image dimensions and destination			
			imgSizeY = int(screen.resY * this->pages[pageNum].itemScaleY);
			imgSizeX = int(textureWidth * (double(imgSizeY) / double(textureHeight))); 
			destX = (screen.resX * this->pages[pageNum].itemX) - (imgSizeX / 2);
			destY = (screen.resY * this->pages[pageNum].itemY) - (imgSizeY / 2);
			//set destination
			destRect = { destX, destY, imgSizeX, imgSizeY };
			//draw texture to buffer
			screen.drawTexture(screen.texture, destRect);
		}

		//draw page text
			//determine how many lines are needed below the text block
			if (this->pages[pageNum].type == "CHOICE") { //adjust size based on number of choices
				endTextSize = this->pages[pageNum].choices.size() * (textFontGap * 2);
			}
			else { //only one thing will be written, so just need one set
				endTextSize = (textFontGap * 2);
			}
			//draw text to texture
			screen.makeTextTexture("fonts/souvenir.ttf", textFontSize, this->pages[pageNum].text, { 50,50,50 }, textWidth);
			//get dimensions
			SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
			//calc text destination
			destX = (screen.resX * this->pages[pageNum].textX) - (textureWidth / 2);
			destY = (screen.resY * this->pages[pageNum].textY) - ((textureHeight + endTextSize) / 2);
			//set destination
			destRect = { destX, destY, textureWidth, textureHeight };
			//prepare end markers 
			endMarkerX = destX;
			endMarkerY = destY + textureHeight + textFontGap;
			//draw texture to buffer
			screen.drawTexture(screen.texture, destRect);

		//draw text at the end of the page depending on page type
		if (this->pages[pageNum].type == "CHOICE") { //write choices
			//loop through choice array and write all choices to the buffer
			for (size_t i = 0; i < this->pages[pageNum].choices.size(); i++) {
				//draw text to texture
				screen.makeTextTexture("fonts/souvenir.ttf", textFontSize, this->pages[pageNum].choices[i].text, { 50,50,50 }, textWidth);
				//get dimensions
				SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
				//set destination
				destRect = { endMarkerX, endMarkerY, textureWidth, textureHeight };
				//draw texture to buffer
				screen.drawTexture(screen.texture, destRect);
				//increment choiceMarkerY
				endMarkerY = (endMarkerY + (textFontGap * 2));
			}
		}
		else { //write text from the page format map
			//draw text to texture
			screen.makeTextTexture("fonts/souvenir.ttf", textFontSize, this->pageFormat[this->pages[pageNum].type].text, { 50,50,50 }, textWidth);
			//get dimensions
			SDL_QueryTexture(screen.texture, NULL, NULL, &textureWidth, &textureHeight);
			//set destination
			destRect = { endMarkerX, endMarkerY, textureWidth, textureHeight };
			//draw texture to buffer
			screen.drawTexture(screen.texture, destRect);
		}

		//render buffer to screen
		screen.renderBuffer();

	}