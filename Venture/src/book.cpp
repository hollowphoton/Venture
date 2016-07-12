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






	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//---------------------------OLD-----------------------------------------------------------------------------------------------------//



	//draw image title
	void Book::drawIntro(Screen &screen) {

		//clean screen
		screen.cleanScreen();
		
		//init vars
		int tempWidth, tempHeight, imgSize, titleFont, authFont, illusFont, maxWidth;
		std::string tempString();

		//set vars
		imgSize = int(screen.resY / 3);
		titleFont = int(screen.resY / 18);
		authFont = int(screen.resY / 45);
		illusFont = int(screen.resY / 60);

		//prep title
		tempString = this->title;
			//draw text to surface
			screen.surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/benguiat_bold.ttf", titleFont), this->title , { 100,100,100 }, txtSpace);
			//create texture
			txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

			SDL_QueryTexture(txtTexture, NULL, NULL, &txtWidth, &txtHeight);






		//draw intro
			//draw title
			screen.renderSurface(txtTexture, txtRect);










		SDL_Texture* titleTexture;
		SDL_Rect titleRect;
		SDL_Texture* authTexture;
		SDL_Rect authRect;
		SDL_Texture* imgTexture;
		SDL_Rect imageRect;
		SDL_Texture* illusTexture;
		SDL_Rect illusRect;


		//p

		//prepare title
			//set screenEdge
			screenEdge = int(screen.resY / 5);
			//draw image to surface
			screen.surface = IMG_Load(imgPath);
			//create texture
			titleTexture = SDL_CreateTextureFromSurface(screen.renderer, screen.surface);
			//get image resolution & ratio
			SDL_QueryTexture(titleTexture, NULL, NULL, &titleWidth, &titleHeight);
			//get image proportions and calculate ratio
			if (titleHeight > titleWidth) {
				titlePortrait = true;
				titleRatio = (double(titleWidth) / double(titleHeight));
			}
			else {
				titlePortrait = false;
				titleRatio = (double(titleHeight) / double(titleWidth));
			}

		//determine title draw size

			//calculate image width & check if the width exceeds window size
			if (titleWidth > screen.resX - (screenEdge * 2)) { 


			}
			else {


			}

			//calculate image height
			titleHeight = int(screen.resY - (screenEdge * 2));

		//calculate width based on imgPortrait
		if (titlePortrait == true) {
			titleWidth = int(titleHeight * titleRatio);
		}
		else {
			titleWidth = int(titleHeight / titleRatio);
		}

		//if imgWidth is still too big for our screen, we need to recalculate
		if (titleWidth > screen.resX - (screenEdge * 2)) {
			//set imgWidth to max available
			titleWidth = screen.resX - (screenEdge * 2);
			//calculate width based on imgPortrait
			if (titlePortrait == true) {
				titleHeight = int(titleWidth / titleRatio);
			}
			else {
				titleHeight = int(titleWidth * titleRatio);
			}
		}

		//calculate vert + horz buffers, then final rect
			//vertical
			titleHBuffer = (screen.resY - (screenEdge * 2) - titleHeight) / 2;
			//horizontal
			titleWBuffer = (screen.resX - (screenEdge * 2) - titleWidth) / 2;
			//calculate titleRect
			titleRect = { (screenEdge + titleWBuffer), (screenEdge + titleHBuffer), titleWidth, titleHeight };

		//draw image where its supposed to go
		screen.draw2screen(titleTexture, titleRect);

		//title hold time
		SDL_Delay(waitTime * 1000);

	}
//--------------------------------------------------------------------------------------------------------------------------------//
























































	//	//draw cave of time title
	//	screen.drawTitle("image", "img/Title.png", "x", 4);
	//	//draw game intro text
	//	screen.drawTitle("text", "x", "This game contains many different adventures you can go on in the Cave of Time. From time to time as you read along, you will be asked to make a choice. Your choice may lead to success or disaster.\n\nThe adventures you take are a result of your choice. You are responsible because you choose!\n\nThink carefully before you make a move! One mistake can be your last . . . or it may lead you to fame and fortune!", 10);





	////load a page                                            REDO REDO REDO REDO REDO REDO REDO REDO
	//void Book::load(Screen &screen, int pageNum) {

	//	//load a page and return the destination that was picked
	//	screen.drawPage(this->pages[pageNum].hasImg, this->pages[pageNum].imgPos, this->pages[pageNum].type, this->pages[pageNum].img, this->pages[pageNum].text, this->pages[pageNum].choices);

	//}








	////prep page
	//void Screen::drawPage(bool hasImg, imageLayout imgPos, pageType pgType, const char* imgPath, const char* textString, std::vector<Choice> choiceArray) {

	//	//clean screen
	//	this->cleanScreen();

	//	//init vars
	//	int imgWidth; //image size x
	//	int imgHeight; //image size y
	//	int imgBuffer; //img vertical buffer
	//	double imgRatio; //img x/y ratio
	//	bool imgPortrait;
	//	int txtSize; //txt font size
	//	int screenEdge;
	//	int sectionDivider; //pixel size of divider between all screen elements
	//	int choiceDivider; //pixel size of divider between all screen elements
	//	int txtWidth; //text pixel width
	//	int txtHeight; //text pixel height
	//	int txtBuffer; //text vertical buffer
	//	int txtSpace; //allotted space that fits text
	//	int choiceWidth; //text pixel width
	//	int choiceHeight; //text pixel height
	//	int choiceSize; //total size of choices needed
	//	int choiceMarkerX; //choice X axis marker
	//	int choiceMarkerY; //choice Y axis marker
	//	int vertBuffer; //buffer for TOP page layout

	//					//init SDL objects
	//	SDL_Texture* txtTexture;
	//	SDL_Texture* imgTexture;
	//	SDL_Texture* choiceTexture;
	//	SDL_Rect txtRect;
	//	SDL_Rect imgRect;
	//	SDL_Rect choiceRect;

	//	//set divider & font size
	//	screenEdge = int(this->resY / 15);
	//	sectionDivider = int(this->resY / 36);
	//	choiceDivider = int(this->resY / 72);
	//	txtSize = int(this->resY / 35);

	//	//prep img (if image exists)
	//	if (hasImg == true) {
	//		//draw image to surface
	//		this->surface = IMG_Load(imgPath);
	//		//create texture
	//		imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//		//get image resolution & ratio
	//		SDL_QueryTexture(imgTexture, NULL, NULL, &imgWidth, &imgHeight);
	//		//determine if image is portrait or landscape, then calc 
	//		if (imgHeight > imgWidth) {
	//			imgPortrait = true;
	//			imgRatio = (double(imgWidth) / double(imgHeight));
	//		}
	//		else {
	//			imgPortrait = false;
	//			imgRatio = (double(imgHeight) / double(imgWidth));
	//		}
	//		//prep image based on imgPos (left, right, or top)
	//		if (imgPos == TOP) {
	//			//calculate image scale (image on top)
	//			imgHeight = int(this->resY / 2.25);
	//			//calculate width based on imgPortrait
	//			if (imgPortrait == true) {
	//				imgWidth = int(imgHeight * imgRatio);
	//			}
	//			else {
	//				imgWidth = int(imgHeight / imgRatio);
	//			}
	//			//if imgWidth is still too big for our screen, we need to recalculate
	//			if (imgWidth > this->resX - (screenEdge * 2)) {
	//				//set imgWidth to max available
	//				imgWidth = this->resX - (screenEdge * 2);
	//				//calculate width based on imgPortrait
	//				if (imgPortrait == true) {
	//					imgHeight = int(imgWidth / imgRatio);
	//				}
	//				else {
	//					imgHeight = int(imgWidth * imgRatio);
	//				}
	//			}
	//		}
	//		else {
	//			//calculate image scale (image on right or left)
	//			imgWidth = int(this->resX / 3.2);
	//			//calculate height based on imgPortrait
	//			if (imgPortrait == true) {
	//				imgHeight = int(imgWidth / imgRatio);
	//			}
	//			else {
	//				imgHeight = int(imgWidth * imgRatio);
	//			}
	//			//if imgHeight is still too big for our screen, we need to recalculate
	//			if (imgHeight > this->resY - (screenEdge * 2)) {
	//				//set imgWidth to max available
	//				imgHeight = this->resY - (screenEdge * 2);
	//				//calculate width based on imgPortrait
	//				if (imgPortrait == true) {
	//					imgWidth = int(imgHeight * imgRatio);
	//				}
	//				else {
	//					imgWidth = int(imgHeight / imgRatio);
	//				}
	//			}
	//		}

	//	}
	//	else {
	//		//load dummy image texture - it wont be used
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", 16), "DUMMY IMAGE", { 100,100,100 }, 100);
	//		imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//	}

	//	//prep text (depending on hasImg)
	//	if (hasImg == true && (imgPos == LEFT || imgPos == RIGHT)) {
	//		//calculate text space based on image being present
	//		txtSpace = this->resX - ((sectionDivider + (screenEdge * 2)) + imgWidth);
	//	}
	//	else {
	//		//calculate text space based on no image or image on top
	//		txtSpace = this->resX - (screenEdge * 2);
	//	}

	//	//draw page text to surface
	//	this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), textString, { 100,100,100 }, txtSpace);
	//	//create texture
	//	txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	//	//draw a single TEST string to surface to identify choice height
	//	this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), "TEST", { 100,100,100 }, 100);
	//	choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	//	//get resolution of txtTexture and choiceTexture
	//	SDL_QueryTexture(txtTexture, NULL, NULL, &txtWidth, &txtHeight);
	//	SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);

	//	//calculate size needed for drawing choice texture(s)
	//	if (pgType == CHOICE) {
	//		//adjust for number of choices
	//		choiceSize = int(choiceArray.size() * (choiceHeight + choiceDivider));
	//	}
	//	else {
	//		//only one thing will be written, so just need one set
	//		choiceSize = int(choiceHeight + choiceDivider);
	//	}

	//	//calculate placement of the text, image, and choices based on pageLayout
	//	if (hasImg == true) {
	//		if (imgPos == LEFT || imgPos == RIGHT) { //placement is LEFT or RIGHT
	//												 //calculate buffers
	//												 //calculate text vertical buffer
	//			txtBuffer = (this->resY - (screenEdge * 2) - (txtHeight + choiceSize)) / 2;
	//			//calculate image vertical buffer
	//			imgBuffer = (this->resY - (screenEdge * 2) - imgHeight) / 2;
	//			//calculate Rects based on orientation
	//			if (imgPos == LEFT) {
	//				//calculate txtRect
	//				txtRect = { ((screenEdge + sectionDivider) + imgWidth), (txtBuffer + screenEdge), txtWidth, txtHeight };
	//				//calculate imgRect
	//				imgRect = { screenEdge, (screenEdge + imgBuffer), imgWidth, imgHeight };
	//				//calculate choiceMarker
	//				choiceMarkerX = ((screenEdge + sectionDivider) + imgWidth);
	//				choiceMarkerY = (screenEdge + txtBuffer + txtHeight);
	//			}
	//			else {
	//				//calculate txtRect
	//				txtRect = { screenEdge, (txtBuffer + screenEdge), txtWidth, txtHeight };
	//				//calculate imgRect
	//				imgRect = { ((screenEdge + sectionDivider) + txtWidth), (screenEdge + imgBuffer), imgWidth, imgHeight };
	//				//calculate choiceMarker
	//				choiceMarkerX = screenEdge;
	//				choiceMarkerY = (screenEdge + txtBuffer + txtHeight);
	//			}
	//		}
	//		else //placement is TOP
	//		{
	//			//calculate buffers
	//			vertBuffer = (this->resY - (imgHeight + ((screenEdge * 2) + sectionDivider) + txtHeight + choiceSize)) / 2;
	//			txtBuffer = (this->resX - (txtWidth)) / 2;
	//			imgBuffer = (this->resX - (imgWidth)) / 2;
	//			//calculate txtRect
	//			txtRect = { txtBuffer, (vertBuffer + imgHeight + screenEdge + sectionDivider), txtWidth, txtHeight };
	//			//calculate imgRect
	//			imgRect = { imgBuffer,  (screenEdge + vertBuffer), imgWidth, imgHeight };
	//			//calculate choiceMarker
	//			choiceMarkerX = txtBuffer;
	//			choiceMarkerY = (screenEdge + vertBuffer + imgHeight + sectionDivider + txtHeight);
	//		}
	//	}
	//	else {
	//		//calculate text vertical buffer
	//		txtBuffer = ((this->resY - (screenEdge * 2)) - (txtHeight + choiceSize)) / 2;
	//		//set text placement
	//		txtRect = { screenEdge, (txtBuffer + screenEdge), txtWidth, txtHeight };
	//		//calculate choiceMarker
	//		choiceMarkerX = screenEdge;
	//		choiceMarkerY = (screenEdge + txtBuffer + txtHeight);
	//	}

	//	//do we need to draw an image?
	//	if (hasImg == true) {
	//		//draw image where its supposed to go
	//		this->draw2screen(imgTexture, imgRect);
	//	}

	//	//draw text where its supposed to go
	//	this->draw2screen(txtTexture, txtRect);

	//	//draw choiceTexture depending on pgType
	//	switch (pgType) {
	//		//CHOICE
	//	case CHOICE:
	//		//loop and draw choices or endings
	//		for (size_t i = 0; i < choiceArray.size(); i++) {
	//			//draw choice to surface to identify choice height
	//			this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), choiceArray[i].text, { 100,100,100 }, txtSpace);
	//			//create texture
	//			choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//			//get resolution of choiceTexture
	//			SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
	//			//set choice rectangle
	//			choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
	//			//draw choice to screen
	//			this->draw2screen(choiceTexture, choiceRect);
	//			//increment choiceMarkerY
	//			choiceMarkerY = (choiceMarkerY + choiceHeight + choiceDivider);
	//		}
	//		break;
	//	case CONTINUE:
	//		//draw choice to surface to identify choice height
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), "Press Enter to continue...", { 100,100,100 }, txtSpace);
	//		//create texture
	//		choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//		//get resolution of choiceTexture
	//		SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
	//		//set choice rectangle
	//		choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
	//		//draw choice to screen
	//		this->draw2screen(choiceTexture, choiceRect);
	//		//break
	//		break;
	//	case DEATH:
	//		//draw choice to surface to identify choice height
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), "YOU ARE DEAD", { 100,100,100 }, txtSpace);
	//		//create texture
	//		choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//		//get resolution of choiceTexture
	//		SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
	//		//set choice rectangle
	//		choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
	//		//draw choice to screen
	//		this->draw2screen(choiceTexture, choiceRect);
	//		//break
	//		break;
	//	case DOOMED:
	//		//draw choice to surface to identify choice height
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), "YOU ARE DOOMED", { 100,100,100 }, txtSpace);
	//		//create texture
	//		choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//		//get resolution of choiceTexture
	//		SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
	//		//set choice rectangle
	//		choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
	//		//draw choice to screen
	//		this->draw2screen(choiceTexture, choiceRect);
	//		//break
	//		break;
	//	case NEW_LIFE:
	//		//draw choice to surface to identify choice height
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), "THE END", { 100,100,100 }, txtSpace);
	//		//create texture
	//		choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//		//get resolution of choiceTexture
	//		SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
	//		//set choice rectangle
	//		choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
	//		//draw choice to screen
	//		this->draw2screen(choiceTexture, choiceRect);
	//		//break
	//		break;
	//	case RETURN_HOME:
	//		//draw choice to surface to identify choice height
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), "THE END", { 100,100,100 }, txtSpace);
	//		//create texture
	//		choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
	//		//get resolution of choiceTexture
	//		SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
	//		//set choice rectangle
	//		choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
	//		//draw choice to screen
	//		this->draw2screen(choiceTexture, choiceRect);
	//		//break
	//		break;
	//	}

	//}

	////draw title
	//void Screen::drawTitle(std::string titleType, const char* imgPath, const char* textString, int waitTime) {

	//	//clean screen
	//	this->cleanScreen();

	//	//draw image
	//	if (titleType == "image") {

	//		//init vars
	//		int imgWidth; //image size x
	//		int imgHeight; //image size y
	//		int hBuffer; //img vertical buffer
	//		int wBuffer; //horizontal buffer
	//		double imgRatio; //img x/y ratio
	//		bool imgPortrait; //img type
	//		int screenEdge; //edge buffer of screen


	//						//init SDL objects
	//		SDL_Texture* imgTexture;
	//		SDL_Rect imgRect;

	//		//set divider & font size
	//		screenEdge = int(this->resY / 6);

	//		//draw image to surface
	//		this->surface = IMG_Load(imgPath);

	//		//create texture
	//		imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	//		//get image resolution & ratio
	//		SDL_QueryTexture(imgTexture, NULL, NULL, &imgWidth, &imgHeight);

	//		//determine if image is portrait or landscape, then calc 
	//		if (imgHeight > imgWidth) {
	//			imgPortrait = true;
	//			imgRatio = (double(imgWidth) / double(imgHeight));
	//		}
	//		else {
	//			imgPortrait = false;
	//			imgRatio = (double(imgHeight) / double(imgWidth));
	//		}

	//		//calculate image scale (image on top)
	//		imgHeight = int(this->resY - (screenEdge * 2));

	//		//calculate width based on imgPortrait
	//		if (imgPortrait == true) {
	//			imgWidth = int(imgHeight * imgRatio);
	//		}
	//		else {
	//			imgWidth = int(imgHeight / imgRatio);
	//		}

	//		//if imgWidth is still too big for our screen, we need to recalculate
	//		if (imgWidth > this->resX - (screenEdge * 2)) {
	//			//set imgWidth to max available
	//			imgWidth = this->resX - (screenEdge * 2);
	//			//calculate width based on imgPortrait
	//			if (imgPortrait == true) {
	//				imgHeight = int(imgWidth / imgRatio);
	//			}
	//			else {
	//				imgHeight = int(imgWidth * imgRatio);
	//			}
	//		}

	//		//calculate image vertical buffer
	//		hBuffer = (this->resY - (screenEdge * 2) - imgHeight) / 2;

	//		//calculate image horizontal buffer
	//		wBuffer = (this->resX - (screenEdge * 2) - imgWidth) / 2;

	//		//calculate imgRect
	//		imgRect = { (screenEdge + wBuffer), (screenEdge + hBuffer), imgWidth, imgHeight };

	//		//draw image where its supposed to go
	//		this->draw2screen(imgTexture, imgRect);

	//	}

	//	//draw text
	//	if (titleType == "text") {

	//		//init vars
	//		int screenEdge;
	//		int txtWidth; //text pixel width
	//		int txtHeight; //text pixel height
	//		int txtSize; //txt font size
	//		int hBuffer; //text vertical buffer
	//		int wBuffer; //text horizontal buffer
	//		int txtSpace; //allotted space that fits text

	//					  //init SDL objects
	//		SDL_Texture* txtTexture;
	//		SDL_Rect txtRect;

	//		//set divider & font size
	//		screenEdge = int(this->resY / 6);
	//		txtSize = int(this->resY / 30);

	//		//calculate text space based on image being present
	//		txtSpace = this->resX - (screenEdge * 2);

	//		//draw page text to surface
	//		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/souvenir.ttf", txtSize), textString, { 100,100,100 }, txtSpace);

	//		//create texture
	//		txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	//		//get resolution of txtTexture
	//		SDL_QueryTexture(txtTexture, NULL, NULL, &txtWidth, &txtHeight);

	//		//calculate text vertical buffer
	//		hBuffer = (this->resY - (screenEdge * 2) - txtHeight) / 2;

	//		//calculate text horizontal buffer
	//		wBuffer = (this->resX - (screenEdge * 2) - txtWidth) / 2;

	//		//set text placement
	//		txtRect = { (screenEdge + wBuffer), (screenEdge + hBuffer), txtWidth, txtHeight };

	//		//draw text where its supposed to go
	//		this->draw2screen(txtTexture, txtRect);

	//	}

	//	//title hold time
	//	SDL_Delay(waitTime * 1000);

	//}