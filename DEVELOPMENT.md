# Project Proposal : Simple multiplayer 2d shooter game
## Libraries: 
  * ~~Raknet (networking engine for games)~~
  * ~~Oxygine (2D C++ game engine)~~
  * ofxCenteredTrueTypeFont (external library for convieniently modifiying font parameters and drawing fonts)
  * ofxNetwork (networking engine)
## Progress:
### April 15:
 * Final project started; created empty openframeworks project with the Oxygine library included.
 * Wall class added; this class contains all walls within a level and has an internal struct which contains the parameters of individual wall segments in the level.
### April 17:
 * No longer using Oxygine library; it is specialized in handling animations which is not needed in the project while lacking the vital collision feature needed for this project.
 * Player class added; contains locations of a player, the cooldown of firing shots and whether the player is alive.
 * Shot class added; contains all shots fired in a level and has an internal struct which contains the parameters of individual shots in the level.
 * Able to detect collision between shots and walls; working on bouncing shots off walls if a collision occurs.
 * _TODO on April 19_: fix collision between shots and walls and add collision between player and walls/ shots and players(easy). Hopefully add game interface (start, settings, etc.).
### April 19:
 * finished implementing shot bouncing and deleting shots after a set number of bounces.
 * implemented shot-player collision; when the player gets hit by a shot they die and become unable to move.
 * implemented player-wall collision; handled border cases such as collision between the player and the corner of a wall.
 * added annotations to existing code
 * _TODO on April 21_: interface for the game; improve robustness of collision algorithms; random wall generation (this turns out to be easier than I thought), in-game units to actual displayed pixels scaling. Hopefully I'll be able to start experimenting with LAN networking on April 22.
### April 21:
 * improved robustness of collision algorithms; fixed cases where resolving a collision between a player/shot and a wall segment will create a new unresolved collision between them and a wall segment previously checked to be fine.
 * added some horrible artwork and sound effects
 * changed display to borderless window due to some weird pixel scaling issues with the title bar
 * added random wall generation and algorithm to prevent overlapping walls (which can cause bugs), walls spawning near the player spawnpoints and walls splitting the level into two with one player on each side.
 * added button class; contains internal struct which contains the parameters of individual buttons.
 * _TODO on April 22_: falling behind in progress due to more time spent on random wall generation than expected; create interface (start, player name, player color, wall density) and add bots to test multiplayer. Start LAN networking part (or at least finish the lobby interface).
### April 22:
 * added interface; the user can now name and choose player color in the main menu. The main menu also contains entrances to single player, multiplayer (not yet implemented), options and exit.
 * added options for the amount of walls to spawn in a level.
 * added pause.
 * added bots; sadly the bot algorithm is not very good and the bot's performance is actual games is suboptimal.
 * added victory condition; the game now properly terminates when only one player is left alive.
 * large modifications to player class and game update cycle; the player class now contains additional variables and some methods in player and in the game update cycle have been modified to account for the existence of bot players.
 * _TODO on April 24_: interface done! Main game is nearly complete at this point and the LAN networking part can be started. Not too much can be said about it since it's hard to say how difficult it would be.
### April 23 (homework was done early so why not):
 * added multiplayer interface; supports entering ip addresses. The planned functionality would be that players on the multiplayer connect page can LAN connect to each other through entering the other's ip address.
 * no longer using Raknet library; for small-scale games like this one involving only 2 players the openFrameworks built-in TCP networking library, ofxNetwork, is more than enough.
 * LAN neworking successfully started; two instances of the game can now connect to each other with one as the host and the other as the client.
 * _TODO on April 24_: set up the main menu for multiplayer to showcase both player models. Figure out how to transmit player data over the connection.
### April 25:
 * added disconnect functionality; either the host or client disconnecting from a multiplayer game will appropriately disconnect the other user.
 * player preview functionality finished! Users can now see a real-time model of their opponents's character in the multiplayer main menu.
 * refactored a lot of code did a project clean-up; moved serialization and de-serialization methods into their respective classes and helper functions in the main program into the helperfunctions class. 
 * _TODO on April 26_: implement (or at least try) the actual multiplayer game and find efficient ways of communication to minimize lag. Move text into a separate "text" class since the current main program looks rather messy with all the "draw text" lying around everywhere.
### April 26:
 * Added text class (called GameText in the program) used to store text to draw in the main program. Makes the main program loop look much cleaner as well as adding future text easier as it is now done separately in the add_button_text class instead of in draw methods in the main program (renamed from add_button).
 * rewrote A LOT of code since before starting the multiplayer game there were many places where the coding style was questionable; modifications include merging some largely similar update/draw functions, rearranging some logical statements, merging similar switch cases and improving class variable naming consistency, and moving initializations/declarations of many variables in the main program into appropriate subclasses and header files.
 * added serialization and deserialization methods for different classes, made possible with a split by delimiter helper function taken from the previous frequencycount assignment.
 * MULTIPLAYER GAME IMPLEMENTED!!! Used approximations of double values to int to reduce lag in multiplayer game, but as observed there is minimal impact on gameplay.
 * _TODO on April 28_ : finishing implementing pause, gameover and exception handling for the multiplayer game. 
### April 27:
 * added appropriate functions for the restart and rematch buttons when pressed in multiplayer. Multiplayer game engine now correctly handles "gameover" moments when not both of the players are alive.
### April 29:
 * added multiplayernetwork class; wrapper class for server and client to simplify the main game engine.
 * further reduced lag by changing data transmission to be "lossy": if multiple messages end up being received in a frame only the newest one is read.
 * added waiting rooms to await confirmation from the other user for operations such as starting games and returning to menu; ensures both players are in sync on the same interface.
 * added text to the multiplayer connect menu to tell the player whether the connection/setting up a server was successful or not.
 * added a disconnected interface shown to users in multiplayer when their partner disconnects. Servers will now also automatically disconnect additional clients when there are more than 1 client connect to it.
 * cleaned up a lot of code; ofApp.cpp down from 900 lines to 650 by moving repeated lines of codes to helper functions; updated comments for differents classes in project, renamed constants and enums according to C++ naming guide.
 * main project done at this point.
 * _TODO on April 30_ : add test cases for different functions to test for robustness, change rgb variables in objects to ofColor objects. If there is still enough time remaining, add a better algorithm for the singleplayer bot.
### April 30:
 * changed all rgb values in objects to ofColor objects.
 * fixed a minor bug with multiplayer engine caused by additional clients connecting to a server.
 * being disconnected from multiplayer now shows whether your game session ended normally or if you connected to a server already playing with another client.
 * _TODO on May 1_ : add test cases for different functions to test for robustness; If there is still enough time remaining, add a better algorithm for the singleplayer bot.
### May 1:
 * FINALLY fixed a minor bug related to shot-wall collision when firing shots at corners (intersection of walls). Previous weird interactions would happen such as the shot dissappearing or the shot bouncing on the same wall twice consecutively and coming back at the shooter (which is mathematically proven to not supposed to happen)
 * added explanations.txt; used for storing diagrams for some of the more math-heavy functions in the program.
 ## Days left to work on project: 0.5 days
* ~~April 31 (half day)~~ proof that studying CS makes you delusional.
* May 1 (half day)
* May 2 (half day, but best not to make any major changes on this day; excluded for now)
