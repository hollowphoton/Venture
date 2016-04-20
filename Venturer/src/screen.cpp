/*
SCREEN CLASS
This class controls SDL, including:
-game window
-drawing graphics
-drawing text
*/

//headers
#include "headers/screen.h"

//--------------------------------------screen class--------------------------------------//

	//constructor
	Screen::Screen(const char* title, int width, int height) {
		//window & renderer
		SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);
		//set window title
		SDL_SetWindowTitle(this->window, title);
		this->resX = width;
		this->resY = height;
		//draw background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
	}

	//destructor
	Screen::~Screen() {
		//renderer
		SDL_DestroyRenderer(this->renderer);
		//window
		SDL_DestroyWindow(this->window);
	}

	//clean screen
	void Screen::cleanScreen() {
		//draw background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//clear surface
		SDL_FillRect(this->surface, NULL, 0x000000);
	}

	//draw page
	void Screen::draw2screen(SDL_Texture* thing, SDL_Rect place) {
		//draw text to screen
		SDL_RenderCopy(this->renderer, thing, NULL, &place);
		SDL_RenderPresent(this->renderer);
	}

	//prep page
	void Screen::drawPage(bool hasImg, imageLayout imgPos, pageType pgType, const char* imgPath, const char* textString, std::vector<Choice> choiceArray) {

		//clean screen
		this->cleanScreen();

		//init vars
		int imgWidth; //image size x
		int imgHeight; //image size y
		int imgBuffer; //img vertical buffer
		double imgRatio; //img x/y ratio
		bool imgPortrait;
		int txtSize; //txt font size
		int sectionDivider; //pixel size of divider between all screen elements
		int choiceDivider; //pixel size of divider between all screen elements
		int txtWidth; //text pixel width
		int txtHeight; //text pixel height
		int txtBuffer; //text vertical buffer
		int txtSpace; //allotted space that fits text
		int choiceWidth; //text pixel width
		int choiceHeight; //text pixel height
		int choiceSize; //total size of choices needed
		int choiceMarkerX; //choice X axis marker
		int choiceMarkerY; //choice Y axis marker
		int vertBuffer; //buffer for TOP page layout

		//init SDL objects
		SDL_Texture* txtTexture;
		SDL_Texture* imgTexture;
		SDL_Texture* choiceTexture;
		SDL_Rect txtRect;
		SDL_Rect imgRect;
		SDL_Rect choiceRect;

		//set divider & font size
		sectionDivider = int(this->resY / 36);
		choiceDivider = int(this->resY / 72);
		txtSize = int(this->resY / 45);

		//prep img (if image exists)
		if (hasImg == true) {
			//draw image to surface
			this->surface = IMG_Load(imgPath);
			//create texture
			imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
			//get image resolution & ratio
			SDL_QueryTexture(imgTexture, NULL, NULL, &imgWidth, &imgHeight);
			//determine if image is portrait or landscape, then calc 
			if (imgHeight > imgWidth) {
				imgPortrait = true;
				imgRatio = (double(imgWidth) / double(imgHeight));
			}
			else {
				imgPortrait = false;
				imgRatio = (double(imgHeight) / double(imgWidth));
			}
			//prep image based on imgPos (left, right, or top)
			if (imgPos == TOP) {
				//calculate image scale (image on top)
				imgHeight = int(this->resY / 2.25);
				//calculate width based on imgPortrait
				if (imgPortrait == true) {
					imgWidth = int(imgHeight * imgRatio);
				}
				else {
					imgWidth = int(imgHeight / imgRatio);
				}
				//if imgWidth is still too big for our screen, we need to recalculate
				if (imgWidth > this->resX - (sectionDivider * 2)) {
					//set imgWidth to max available
					imgWidth = this->resX - (sectionDivider * 2);
					//calculate width based on imgPortrait
					if (imgPortrait == true) {
						imgHeight = int(imgWidth / imgRatio);
					}
					else {
						imgHeight = int(imgWidth * imgRatio);
					}
				}
			}
			else {
				//calculate image scale (image on right or left)
				imgWidth = int(this->resX / 3.2);
				//calculate height based on imgPortrait
				if (imgPortrait == true) {
					imgHeight = int(imgWidth / imgRatio);
				}
				else {
					imgHeight = int(imgWidth * imgRatio);
				}
				//if imgHeight is still too big for our screen, we need to recalculate
				if (imgHeight > this->resY - (sectionDivider * 2)) {
					//set imgWidth to max available
					imgHeight = this->resY - (sectionDivider * 2);
					//calculate width based on imgPortrait
					if (imgPortrait == true) {
						imgWidth = int(imgHeight * imgRatio);
					}
					else {
						imgWidth = int(imgHeight / imgRatio);
					}
				}
			}

		}
		else {
			//load dummy image texture - it wont be used
			this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "DUMMY IMAGE", { 100,100,100 }, 100);
			imgTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
		}

		//prep text (depending on hasImg)
		if (hasImg == true && (imgPos == LEFT|| imgPos == RIGHT)) {
			//calculate text space based on image being present
			txtSpace = this->resX - ((sectionDivider * 3) + imgWidth);
		}
		else {
			//calculate text space based on no image or image on top
			txtSpace = this->resX - (sectionDivider * 2);
		}

		//draw page text to surface
		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), textString, { 100,100,100 }, txtSpace);
		//create texture
		txtTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

		//draw a single TEST string to surface to identify choice height
		this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "TEST", { 100,100,100 }, 100);
		choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

		//get resolution of txtTexture and choiceTexture
		SDL_QueryTexture(txtTexture, NULL, NULL, &txtWidth, &txtHeight);
		SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);

		//calculate size needed for drawing choice texture(s)
		if (pgType == CHOICE) {
			//adjust for number of choices
			choiceSize = int(choiceArray.size() * (choiceHeight + choiceDivider));
		}
		else {
			//only one thing will be written, so just need one set
			choiceSize = int(choiceHeight + choiceDivider);
		}

		//calculate placement of the text, image, and choices based on pageLayout
		if (hasImg == true) {
			if (imgPos == LEFT || imgPos == RIGHT) { //placement is LEFT or RIGHT
				//calculate buffers
					//calculate text vertical buffer
					txtBuffer = (this->resY - (sectionDivider * 2) - (txtHeight + choiceSize)) / 2;
					//calculate image vertical buffer
					imgBuffer = (this->resY - (sectionDivider * 2) - imgHeight) / 2;
				//calculate Rects based on orientation
				if (imgPos == LEFT) {
					//calculate txtRect
					txtRect = { ((sectionDivider * 2) + imgWidth), (txtBuffer + sectionDivider), txtWidth, txtHeight };
					//calculate imgRect
					imgRect = { sectionDivider, (sectionDivider + imgBuffer), imgWidth, imgHeight };
					//calculate choiceMarker
					choiceMarkerX = ((sectionDivider * 2) + imgWidth);
					choiceMarkerY = (sectionDivider + txtBuffer + txtHeight);
				}
				else {
					//calculate txtRect
					txtRect = { sectionDivider, (txtBuffer + sectionDivider), txtWidth, txtHeight };
					//calculate imgRect
					imgRect = { ((sectionDivider * 2) + txtWidth), (sectionDivider + imgBuffer), imgWidth, imgHeight };
					//calculate choiceMarker
					choiceMarkerX = sectionDivider;
					choiceMarkerY = (sectionDivider + txtBuffer + txtHeight);
				}
			}
			else //placement is TOP
			{
				//calculate buffers
				vertBuffer = (this->resY - (imgHeight + (sectionDivider * 2) + txtHeight + choiceSize)) / 2;
				txtBuffer = (this->resX - (txtWidth)) / 2;
				imgBuffer = (this->resX - (imgWidth)) / 2;
				//calculate txtRect
				txtRect = { txtBuffer, (vertBuffer + imgHeight + sectionDivider), txtWidth, txtHeight };
				//calculate imgRect
				imgRect = { imgBuffer,  (sectionDivider + vertBuffer), imgWidth, imgHeight };
				//calculate choiceMarker
				choiceMarkerX = txtBuffer;
				choiceMarkerY = (sectionDivider + vertBuffer + imgHeight + sectionDivider + txtHeight);
			}
		}
		else {
			//calculate text vertical buffer
			txtBuffer = ((this->resY - (sectionDivider * 2)) - (txtHeight + choiceSize)) / 2;
			//set text placement
			txtRect = { sectionDivider, (txtBuffer + sectionDivider), txtWidth, txtHeight };
			//calculate choiceMarker
			choiceMarkerX = sectionDivider;
			choiceMarkerY = (sectionDivider + txtBuffer + txtHeight);
		}

		//do we need to draw an image?
		if (hasImg == true) {
			//draw image where its supposed to go
			this->draw2screen(imgTexture, imgRect);
		}

		//draw text where its supposed to go
		this->draw2screen(txtTexture, txtRect);

		//draw choiceTexture depending on pgType
		switch (pgType) {
			//CHOICE
			case CHOICE:
				//loop and draw choices or endings
				for (size_t i = 0; i < choiceArray.size(); i++) {
					//draw choice to surface to identify choice height
					this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), choiceArray[i].text, { 100,100,100 }, txtSpace);
					//create texture
					choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
					//get resolution of choiceTexture
					SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
					//set choice rectangle
					choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
					//draw choice to screen
					this->draw2screen(choiceTexture, choiceRect);
					//increment choiceMarkerY
					choiceMarkerY = (choiceMarkerY + choiceHeight + choiceDivider);
				}
				break;
			case CONTINUE:
				//draw choice to surface to identify choice height
				this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "Press Enter to continue...", { 100,100,100 }, txtSpace);
				//create texture
				choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
				//get resolution of choiceTexture
				SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
				//set choice rectangle
				choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
				//draw choice to screen
				this->draw2screen(choiceTexture, choiceRect);
				//break
				break;
			case DEATH:
				//draw choice to surface to identify choice height
				this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "YOU ARE DEAD", { 100,100,100 }, txtSpace);
				//create texture
				choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
				//get resolution of choiceTexture
				SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
				//set choice rectangle
				choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
				//draw choice to screen
				this->draw2screen(choiceTexture, choiceRect);
				//break
				break;
			case DOOMED:
				//draw choice to surface to identify choice height
				this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "YOU ARE DOOMED", { 100,100,100 }, txtSpace);
				//create texture
				choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
				//get resolution of choiceTexture
				SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
				//set choice rectangle
				choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
				//draw choice to screen
				this->draw2screen(choiceTexture, choiceRect);
				//break
				break;
			case NEW_LIFE:
				//draw choice to surface to identify choice height
				this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "THE END", { 100,100,100 }, txtSpace);
				//create texture
				choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
				//get resolution of choiceTexture
				SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
				//set choice rectangle
				choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
				//draw choice to screen
				this->draw2screen(choiceTexture, choiceRect);
				//break
				break;
			case RETURN_HOME:
				//draw choice to surface to identify choice height
				this->surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("fonts/segoeuil.ttf", txtSize), "THE END", { 100,100,100 }, txtSpace);
				//create texture
				choiceTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
				//get resolution of choiceTexture
				SDL_QueryTexture(choiceTexture, NULL, NULL, &choiceWidth, &choiceHeight);
				//set choice rectangle
				choiceRect = { choiceMarkerX, choiceMarkerY, choiceWidth, choiceHeight };
				//draw choice to screen
				this->draw2screen(choiceTexture, choiceRect);
				//break
				break;
		}

	}