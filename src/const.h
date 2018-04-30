#pragma once

/*
message for a failed connection attempt to a server.
*/
static const char* kConnectFail = "Connection failed. Please try again.";

/*
message for successfully hosting a server.
*/
static const char* kHostingServer = "you are now hosting a server. Please wait for another user to connect.";

/*
message for clicking the 'create server' button when already hosting a server.
*/
static const char* kAlreadyHost = "you are already hosting a server.";

/*
message for failing to host a server, usually due to another instance of the program hosting a server on the same machine.
*/
static const char* kServerConflict = "setup failed; there is already a server running on this machine.";

/*
pi. self-explanatory.
*/
const double kPi = 3.14159265359;

/*
width of the level; not necessarily the window width.
*/
const int kLevelWidthMultiplier = 32;

/*
height of the level; not necessarily the window height.
*/
const int kLevelHeightMultiplier = 24;

/*
guideline width for creating wall segments.
*/
const int kWallWidth = 32;

/*
radius of the player (who is a circle).
*/
const int kPlayerRadius = 15;

/*
radius of shots.
*/
const int kShotRadius = 3;

/*
velocity of the player.
*/
const int kPlayerVelocity = 4;

/*
cooldown between firing shots in ticks.
*/
const int kPlayerShotCooldown = 30;

/*
the "length" of a shot; only used in shot-wall collisions to calculate trajectory; has nothing to do with shot-player collisions.
*/
const int kShotLength = 12;

/*
buffer value used in resolving collisions.
*/
const double kEpsilon = 0.00005;

/*
amount of times a shot can bounce.
*/
const int kShotBounces = 6;

/*
the cooldown between the bot changing directions. Unused by players.
*/
const int kBotChangeDirectionCd = 30;

/*
the maximum name length of the player.
*/
const int kMaxNameLength = 16;

/*
the maximum ip address length. (e.g. 255.255.255.255 - exactly 15 characters).
*/
const int kMaxIpLength = 15;
/*
direction enum; used to determine the player's orientation.
*/
enum Direction { STOP = 0, NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, NORTHWEST = 6, SOUTHEAST = 7, SOUTHWEST = 8 };

/*
game state enum; used for determining what interface the program is in.
*/
enum GameState { MAIN_MENU = 0, IN_GAME_SINGLE = 1, IN_GAME_MULTI = 2, PAUSE = 3, ROUND_OVER = 4, HELP = 5,
	MULTI_CONNECT = 6 , MULTI_MENU = 7, WAITING_ROOM = 8, DISCONNECTED = 9};

/*
enum for connection status of the program.
*/
enum Connection { NONE = 0, HOST = 1, CLIENT = 2 };

/*
indices of Buttons in the AllButtons object.
*/
//single player menu buttons
const int kStartSingleplayerButton = 0;
const int kStartMultiplayerButton = 1;
const int kHelpButton = 2;
const int kExitButton = 3;
const int kRedPalette = 4;
const int kGreenPalette = 5;
const int kBluePalette = 6;
const int kYellowPalette = 7;
const int kMagentaPalette = 8;
const int kCyanPalette = 9;
const int kFewWallsButton = 10;
const int kMediumWallsButton = 11;
const int kALotWallsButton = 12;

//paused buttons
const int kPausedToMenuButton = 13;

//help buttons
const int kHelpToMenuButton = 14;

//round over buttons
const int kRematchButton = 15;
const int kRoundOverToMenuButton = 16;

//multiplayer connect buttons
const int kConnectToServerButton = 17;
const int kStartServerButton = 18;
const int kMultiConnectToMenuButton = 19;

//multiplayer menu buttons
const int kMultiDisconnectButton = 20;

//disconnected menu buttons
const int kDisconnectConfirmButton = 21;

/*
constants for color codes of the player
*/
const int kRedColor = 0;
const int kGreenColor = 1;
const int kBlueColor = 2;
const int kYellowColor = 3;
const int kMagentaColor = 4;
const int kCyanColor = 5;

/*
constants for the amount of walls to be generated in a level; corresponds to the wall setting buttons.
*/
const int kFewWallsAmount = 8;
const int kMediumWallsAmount = 16;
const int kALotWallsAmount = 32;

/*
start and end of printable ascii character range.
*/
const int kCharacterStart = 32;
const int kCharacterEnd = 126;

/*
start and end of printable integer character range.
*/
const int kIntegerStart = 48;
const int kIntegerEnd = 57;

/*
ascii value of backspace button.
*/
const int kBackspaceAscii = 8;

/*
ascii value of period.
*/
const int kPeriodAscii = 46;

/*
port number used for multiplayer connections. (Fixing this makes so that only one multiplayer server can be started per ip address).
*/
const int kMultiplayerPort = 11999;

