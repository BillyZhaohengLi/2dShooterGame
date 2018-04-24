# Project Proposal : Simple multiplayer 2d shooter game
## Libraries: 
  * Raknet (networking engine for games)
  * Oxygine (2D C++ game engine) (no longer using)
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
## Days left to work on project: 5 days
* April 24 (half day)
* April 25 (half day)
* April 26 (half day)
* April 27 (half day)
* April 28 (full day)
* April 29 (full day)
* April 30 (half day)
* April 31 (half day)
