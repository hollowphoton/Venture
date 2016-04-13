/*
PAGE.H
This is the header file for the page class
*/

#ifndef PAGE_H
#define PAGE_H

//headers
#include <string>

//page choice class
class pageChoice
{
public:
	//vars
	int choice_id = 0;
	std::string choice_text;
	std::string choice_done;
	int room_dest = 0;
	//constructor
	pageChoice();
	//methods
protected:
private:
};

//book page class
class bookPage
{
public:
	//vars
	int room_id = 0;
	std::string room_type;
	std::string room_text;
	std::string room_img;
	//pageChoice choices[];
	//constructor
	bookPage();
	//methods
protected:
private:
};

#endif //end definition check