#include "GameHud.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include <iomanip>
#include <sstream>

GameHud::GameHud(const sf::Vector2f& pos, const sf::Vector2f& size)
	: _rect(size), _newRecord(size) {

	//Load the font
	ResourcesManager::getInstance().loadFont(GAME_FONT);

	

	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::Transparent);

	_score.setPosition({ 0, 5 });
	_score.setFont(ResourcesManager::getInstance().getFont());
	_score.setCharacterSize(25);
	_score.setFillColor(sf::Color::White);
	_score.setOutlineThickness(0.8f);
	_score.setOrigin(_score.getLocalBounds().left, _score.getLocalBounds().top);

	_life.setPosition({ 180,5 });
	_life.setFont(ResourcesManager::getInstance().getFont());
	_life.setCharacterSize(25);
	_life.setFillColor(sf::Color::White);
	_life.setOutlineThickness(0.8f);
	_life.setOrigin(_life.getLocalBounds().left, _life.getLocalBounds().top);

	_level.setPosition({ 320,5 });
	_level.setFont(ResourcesManager::getInstance().getFont());
	_level.setCharacterSize(25);
	_level.setFillColor(sf::Color::White);
	_level.setOutlineThickness(0.8f);
	_level.setOrigin(_level.getLocalBounds().left, _level.getLocalBounds().top);

	_speed.setPosition({ 470,5 });
	_speed.setFont(ResourcesManager::getInstance().getFont());
	_speed.setCharacterSize(25);
	_speed.setFillColor(sf::Color::White);
	_speed.setOutlineThickness(0.8f);
	_speed.setOrigin(_speed.getLocalBounds().left, _speed.getLocalBounds().top);

	_score.setString(SCORE_PREFIX);
	_level.setString(LEVEL_PREFIX);
	_life.setString(LIFE_PREFIX);
	_speed.setString(SPEED_PREFIX);

	_menu = std::make_unique<Menu>(size);

	_currentData._gameOver = false;
}

GameHud::~GameHud() {}

void GameHud::update(const GameData& data) {
	//Checks if started, paused, gameovered
	if (_currentData._started == !data._started) {
		_menu->showMenu(!data._started, false);
	}  else if(_currentData._started == true &&
			  data._isPaused != _currentData._isPaused) {
		_menu->showMenu(data._isPaused, data._isPaused);
	} else if (data._gameOver != _currentData._gameOver) {
		_menu->showMenu(data._gameOver, false);
	}

	_score.setString(SCORE_PREFIX + std::to_string(data._score));
	_level.setString(LEVEL_PREFIX + std::to_string(data._level));
	_life.setString(LIFE_PREFIX + std::to_string(data._life));

	std::ostringstream streamObj3;
	// Set Fixed -Point Notation
	streamObj3 << std::fixed;

	// Set precision to 2 digits
	streamObj3 << std::setprecision(2);

	//Add double to stream
	streamObj3 << data._speed;


	_speed.setString(SPEED_PREFIX + streamObj3.str());


	if (data._isNewRecord && !_currentData._isNewRecord) {
		_menu->mute(true);
		_newRecord.setMute(false);
		_newRecord.update(_currentData._score);
	} else if (!data._isNewRecord && _currentData._isNewRecord) {
		_menu->mute(false);
	}

	_currentData = data;
}

sf::Vector2f GameHud::getCenter() const {
	//TODO
	return sf::Vector2<float>();
}

void GameHud::draw(sf::RenderWindow & window) const {
	window.draw(_rect);
	if (_currentData._started) {
		for (int i = 0; i < _drawables.size(); i++) {
			_drawables[i]->draw(window);
		}

		window.draw(_score);
		window.draw(_level);
		window.draw(_life);
		window.draw(_speed);
	} 
	_menu->draw(window);
	if (_currentData._isNewRecord)
		_newRecord.draw(window);
}

