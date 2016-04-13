/*
PAGE.H
This is the header file for the page class
*/

#ifndef PAGE_H
#define PAGE_H

//headers
#include <string>
#include <vector>

//page choice class
class pageChoice
{
public:
	//vars
	int choice_id = 0;
	std::string choice_text;
	std::string choice_past;
	int room_dest = 0;
	//methods
	pageChoice(); //constructor
	~pageChoice(); //destructor
private:
};

//book page class
class bookPage
{
public:
	//vars
	int room_id = 0;
	std::string room_type;
	const char* room_text;
	const char* room_img;
	std::vector<pageChoice> choices;
	//methods
	bookPage(); //constructor
	~bookPage(); //destructor
	void makeFake(); //assign demo book page vars
	void load(); //load the page 
private:
};

#endif