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
## Days left to work on project: 6 days
* April 21 (full day)
* April 22 (full day)
* April 24 (half day)
* April 25 (half day)
* April 26 (half day)
* April 27 (half day)
* April 28 (full day)
* April 29 (full day)
