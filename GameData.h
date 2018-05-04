#pragma once

//Struct of the game data
struct GameData {
	int _level;
	int _score;
	int _life;
	bool _isPaused;
	bool _gameOver;
	bool _started;
	double _speed;
	bool _exit;
	bool _isNewRecord;
};