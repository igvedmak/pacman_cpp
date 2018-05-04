#pragma once
#include <string>

using std::string;

//Events
const string ON_MOUSE_DOWN = "onMouseDown";
const string ON_MOUSE_UP = "onMouseUp";
const string ON_MOUSE_MOVE = "onMouseMove";
const string ON_KEY_PRESSED = "onKeyPressed";
const string ON_TEXT_ENTERED = "onTextEntered";
const string ON_MOVE = "onMove";
const string ON_GAME_START = "onGameStart";
const string ON_GAME_EXIT = "onGameExit";
const string ON_GAME_RESUME = "onGameResume";
const string ON_SOUND_STATE_CHANGED = "onSoundChange";
const string ON_NEW_RECORD_END = "onNewRecordEnd";

enum TextureColor {
	Red = 0,
	Green,
	Blue
};

enum TextureType {
	PacmanTexture = 0,
	ElfTexture,
	WallTexture,
	CookieTexture
};

enum Direction {
	Up = 0,
	Down,
	Left,
	Right,
	None
};

enum Interaction {
	CookieInteraction = 0,
	EnemyInteraction,
	NoneInteraction
};

enum CookieType {
	PotionCookie = 0,
	HealthCookie,
	RegularCookie
};

//Moveables speed  constants
const int DEFAULT_SPEED = 100;
const int DEFAULT_ELF_SPEED = 150;
const int MAX_SPEED = 300;

//Game defaults
const int SPRITE_SIZE = 100;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 750;
const int GAME_FPS = 60;

//Elf constants
const float UPDATE_STUPID_ELF_SEC = 0.2f;
const float UPDATE_BFS_SEC = 0.5f;

//Cookie constants
const int POSTION_COOKIE_SEC = 7;
const double POSTION_COOKIE_FACTOR = 0.9;
const int HEALTH_COOKIE_SEC = 14;
const double HEALTH_COOKIE_FACTOR = 1.2;

//Resources constants
const string FILE_PREFIX = "Resources/Levels/level_";
const string FILE_POSTFIX = ".txt";
const string BG_SOUND = "Resources/Sounds/bgsound.ogg";
const string CK_SOUND = "Resources/Sounds/CK.ogg";
const string MOUSE_OVER_SOUND = "Resources/Sounds/MouseOver.ogg";
const string GAME_OVER_SOUND = "Resources/Sounds/GameOver.ogg";
const string NEXT_LEVEL_SOUND = "Resources/Sounds/NextLevel.ogg";
const string GAME_TEXTURES = "Resources/sprites.png";
const string GAME_FONT = "C:\\Windows\\Fonts\\COUR.TTF";
const string BG_TEXTURE = "Resources/bg.png";
const string HIGH_SCORE_FILE = "Resources/HighScore.txt";

//Hud constants
const string SCORE_PREFIX = "Score:";
const string LIFE_PREFIX = "Life:";
const string LEVEL_PREFIX = "Level:";
const string SPEED_PREFIX = "Speed:";

//New record constants
const string NEW_RECORD_TITLE = "Its A New RECORD !!!";
const string NEW_RECORD_ENTER_NAME = "Please enter your name: (Enter to end)";
const string YOUR_RECORD_TITLE = "Your Record is:";
const string LAST_RECORD_TITLE = "Last Record was:";
const int MAX_NAME = 10;

//Menu constants
const string MENU_RESUME = "Resume";
const string MENU_NEW_GAME = "New Game";
const string MENU_TOGGLE_SOUND = "Toggle Sound";
const string MENU_EXIT = "Exit";