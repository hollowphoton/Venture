=======================================================================
         Choose Your Own Adventure: The Cave of Time: The Game         
=======================================================================
A digital version of the classic first entry in the popular series of
choose your own adventure books. The goal of this application is to
replicate the feeling of reading one of these books, while also having
the helpful features and systems that most modern games employ.


===============================-UP NEXT-===============================
Next:
-text spacing for choices (after page txt) seems to differ page to page
-make the page elements a little further away from the screen edge
-add intro title for hollowphoton, the book name, and instructions page
-add header
-add mouse clicks for selecting options
-make the book class have the xml path as a parameter again

Later:
-watch memory usage (currently sits bewtween 25-50MB)
-preload images possible?
-do i need to pass 'screen' with the book.load() function?
-make excel output the XML file? then we dont have to worry
 about find/replace? would be nice if it could auto-dump into the
 project folders too.

===============================-CHANGES-===============================
2016-04-19 - Round II
---------------------
-created debug mode that runs through all possible pages (for testing)
-fixed issue where pages were rendered in an infinite loop while it
 waited for a key to be pressed. I now call the first page to be
 rendered before the main quit loop, and only draw new pages when a
 choice is made.
-Crashes resolved: mouse movement, idle time
-page draw issues occured with TOP layouts where the image was scaled
 incorrectly due to imgPortrait being judged incorrectly.
-fixed the vertical centering of page elements. It turned out to be an
 issue with missing sectionDivider vars in some formulas.
-made choices darker and a non-light font to make them stand out.

2016-04-19
----------
-realized the issue was data type conversion issues, fixed those
-Got the window to render but \n and input doesnt work
-Got inputs working! 
-Had an issue with SDL objects not clearing, new pages wrote on top
 of old ones. Fixed that with a new clearScreen() method
-game now works and strange pixelated text issue is gone! It's playable
-fixed issue with if statement comparing char* and string
	-used if(strcompare(char*,string) ==0){} instead
-fixed image scaling depending on portrait vs. landscape
-fixed text placement bug when no image is on screen
-fixed new line character formatting 
-fixed issue with using wrong ENUM type in imageLayout check
-increased size of TOP image to resY/2.25
-fixed image scaling if default calc made it go off the page
-deleted makeFake()
-MADE THE FIRST PLAYABLE BUILD!!!! Feels good.

2016-04-18
----------
-added ENUMs for pageLayout and pageType
-wrote first draft of game loop using a switch
-added keypress detection for 1,2,3,4 for choices
-made formatting identical across all .h and .cpp files
-made page load paths: left, right, top, none
-built XML ingestor that sits inside the book constructor
-made a map to translate strings to the ENUMs I created
-patch after first run test:
	-renamed pageLayout ENUM to imageLayout
	-moved ENUMs to a global.h
	-redid header #includes
	-learned about forward includes and used a few of those
	-removed an unused variable
	-put an IF wrapper around draw image since its not always needed
-realized the last error was in the XML ingestion
	-found that the initial ingest was broken
	-added file and doc as private vars in the book class
	-still no luck

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

