=======================================================================
         Choose Your Own Adventure: The Cave of Time: The Game         
=======================================================================
A digital version of the classic first entry in the popular series of
choose your own adventure books. The goal of this application is to
replicate the feeling of reading one of these books, while also having
the helpful features and systems that most modern games employ.


===============================-UP NEXT-===============================
Next:
-make formatting identical across all .h and .cpp files
	-like page.h and page.cpp
-add header image to screen method
-make 3 paths for imgPos: left,right,top (L+R should use same code)
-create book methods:
	-ingest xml and create book
		-only create specified number of pages
		-only create specified number of choices

Later:
-add in hp intro, title, and cyoa intro slide
-preload images possible?


===============================-CHANGES-===============================
2016-04-17
----------
-finished photoshopping all page images
-updated and finalized xml macro
-created final xml file for Cave of Time
-simplified page class (-> book class & screen class)
-created book class to house pages

2016-04-16
----------
-simplified the xml format that the Excel macro produces
-worked a bit on the XML ingestion
-worked on photoshoping page images

2016-04-14
----------
-fixed image scaling, ended up changing a renderer setting
-updated page and screen class - near final
-redid XML automation (Excel) to add page number to the main node
-started XML ingestion
	-decided to go with opening the xml each time page loads
	-not sure if this is a good choice?
	-should I keep all of the xml file in memory?

2016-04-13
----------
-moved lots of stuff out of game class and into the page class, added:
	-auto text scaling based on game res
	-auto image scaling based on game res
	-auto placement of image and text based on game res

2016-04-12
----------
-redid entire project from scratch
	-new project
	-new folder structure
	-added SDL2_image
-got the first CyoaCave example working with classes
	-game & screen classes created

2016-04-10
----------
-made an Excel macro that creates an XML file from 2 book tables
-full XML file for entire book completed

2016-04-08
----------
-planned out classes some more
-created the XML schema for the book, added a few entries

2016-04-08
----------
-implemented first pass of classes
-added past tense versions of all choices in the book

2016-03-13
----------
-integrated SDL2
	-created screen and renderer
	-drew image to window
	-drew text to window
	-learned create/destroy

2016-03-12
----------
-typed the entire book into Excel
-designed page/choice structure

