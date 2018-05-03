# CS 126 FinalProject - 2D Shooter Game
## Development background
* This project was developed and compiled using Visual Studio 2017 with a Windows 7 OS.

## How do I play the game?
* The instructions are contained inside the game viewable by clicking the "Help" button seen in the main menu and are rather self-explanatory; follow the prompts in the individual interfaces.
* There are no textboxes whatsoever in the program; player names and ip addresses are both entered by directly typing with the program open.
* Currently multiplayer is supported for LAN connect only and between 2 players.

## How do I build this thing?
 * All you need to compile the project are the code files in the src folder and the sound and text files in resources folder. Depending on the IDE used, either put the files in the resources folder into the src folder (in the SAME level as main.cpp) or put them into YourProjectName/bin/data if using Visual studio, where 'bin' should in the same level as the src folder.
 
## Unit testing
 * Not convinced that the game works? Go into the ofApp.h file and uncomment the test headers, then go into the ofApp.cpp file and uncomment the test methods, and read the test output in your console.
 * More test cases can be added to the test files located in src/test. Just follow the format of the existing test cases (or simply look at UNIT_TEST.h, a custom-created unit test class for this project).
 
## Resources used
 * Make sure to include the ofxGui and ofxNetwork libraries when building the project.
 * The sounds used in the game are taken from Counter Strike 1.6; the shot sound and the death sound are the P2000 firing sound and death sound used in Counter Strike 1.6 respectively. 
 * The text, Verdana.ttf is taken from openFrameworks.
 * Various helper functions in the helperfunction file were "derived" from stackoverflow and geeksforgeeks.

## Required dlls for building on Windows (x32):
* assimp.dll
* concrt140d.dll
* fmodex.dll
* fmodexL.dll
* FreeImage.dll
* freetype.dll
* glut32.dll
* libeay32.dll
* msvcp140_1d.dll
* msvcp140d.dll
* ssleay32.dll
* urctbased.dll
* vccorlib140d.dll
* vcruntime140d.dll
* Zlib.dll
