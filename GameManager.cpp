#include "GameManager.h"
#include "Cookie.h"
#include "EventsManager.h"
#include "SoundsManager.h"
#include "GameClock.h"
#include "CollisionMap.h"
#include "ResourcesManager.h"
#include <thread>

GameManager::GameManager(sf::VideoMode _winSize) {
	//Listen to game events
	EventsManager::getInstance().subscribe(ON_GAME_START, *this);
	EventsManager::getInstance().subscribe(ON_GAME_EXIT, *this);
	EventsManager::getInstance().subscribe(ON_GAME_RESUME, *this);
	EventsManager::getInstance().subscribe(ON_SOUND_STATE_CHANGED, *this);
	EventsManager::getInstance().subscribe(ON_NEW_RECORD_END, *this);

	//Add collisions to CollisionMap
	CollisionMap::getInstance().addEntry("class Pacman", "class Cookie", 
		[&](GameObject& pacman, GameObject& cookie) { 
			pacmanCookie(pacman, cookie);
	});

	CollisionMap::getInstance().addEntry("class Pacman", "class Elf",
		[&](GameObject& pacman, GameObject& elf) {
			pacmanElf(pacman, elf);
	});

	//Set the screen and the hud
	_screen = std::make_unique<GameScreen>(sf::Vector2f(0, 50), sf::Vector2f((float)_winSize.width, (float)_winSize.width));
	_hud = std::make_unique<GameHud>(sf::Vector2f(0, 0), sf::Vector2f((float)_winSize.width, (float)_winSize.height));

	_data._gameOver = false;
	_data._isPaused = false;
	_data._level = 1;
	_data._life = 3;
	_data._score = 0;
	_data._started = false;
	_data._exit = false;
	_data._isNewRecord = false;

	SetSounds();
}

GameManager::~GameManager() {
	//Remove listen to game events
	EventsManager::getInstance().unsubscribe(ON_GAME_START, *this);
	EventsManager::getInstance().unsubscribe(ON_GAME_EXIT, *this);
	EventsManager::getInstance().unsubscribe(ON_GAME_RESUME, *this);
	EventsManager::getInstance().unsubscribe(ON_SOUND_STATE_CHANGED, *this);
	EventsManager::getInstance().unsubscribe(ON_NEW_RECORD_END, *this);

}

bool GameManager::update(sf::Event event) {
	if (_data._exit) {
		return false;
	}

	//If game started
	if (_data._started && !_data._gameOver) {
		_screen->updateAI();
		EventsManager::getInstance().fireEvent(ON_MOVE, event);
		handleInteractions();
		_data._speed = _screen->getPacman().getSpeed();
	}

	_hud->update(_data);
	return true;
}

void GameManager::handleInteractions() {
	auto interaction = _screen->getInteraction();

	CollisionMap::HitFunctionPtr phf = CollisionMap::getInstance().lookup("class Pacman",
																		  typeid(interaction.second).name());
	if (phf) 
		phf(_screen->getPacman(), interaction.second);
}

void GameManager::pacmanCookie(GameObject & pacman, GameObject & cookie) {
	auto& cookieObject = dynamic_cast<Cookie&>(cookie);
	SoundsManager::getInstance().playSound(CK_SOUND);

	//Checks cookie type
	switch (cookieObject.getCookieType()) {
		case RegularCookie:
			break;
		case PotionCookie:
			if (_screen->getPacman().getSpeed() > DEFAULT_SPEED)
				_screen->getPacman().setSpeedFactor(POSTION_COOKIE_FACTOR, POSTION_COOKIE_SEC);
			break;
		case HealthCookie:
			if (_screen->getPacman().getSpeed() < MAX_SPEED*1.3)
				_screen->getPacman().setSpeedFactor(HEALTH_COOKIE_FACTOR, HEALTH_COOKIE_SEC);
			break;
	}

	_data._score += (_screen->getElfsCount() + 1) * 2;

	_screen->removeGameObjectFromGrid(_screen->getPacmanGrisPos());

	//Checks screen cookies count
	if (_screen->getCookiesCount() == 0) {
		SoundsManager::getInstance().playSound(NEXT_LEVEL_SOUND);
		_data._score += (_screen->getElfsCount() + 1) * 50;
		_data._level++;
		_screen->muteEvents(true);
		if (!_screen->loadLevel(_data._level)) {
			SoundsManager::getInstance().playSound(GAME_OVER_SOUND);
			gameOver();
		}
	}
	
}

void GameManager::pacmanElf(GameObject & pacman, GameObject & elf) {
	_data._life--;
	SoundsManager::getInstance().playSound(GAME_OVER_SOUND);
	//Checks the life
	if (_data._life == 0) {
		gameOver();
	} else {
		_screen->resetLevel();
	}
}

GameScreen& GameManager::getGameScreen() {
	return *_screen;
}

GameHud& GameManager::getGameHud() {
	return *_hud;
}

bool GameManager::keyPressed(const sf::Event& event) {
	switch (event.key.code) {
		case sf::Keyboard::Escape:
			if (_data._started && !_data._gameOver) {
				_data._isPaused = !_data._isPaused;
				_screen->muteEvents(_data._isPaused);
				_hud->update(_data);
				return true;
			}
			break;
	}
	return false;
}

bool GameManager::textEntered(const sf::Event & event) {
	return false;
}

void GameManager::SetSounds() {
	SoundsManager& sm = SoundsManager::getInstance();

	sm.addSound(BG_SOUND, 20);
	sm.addSound(CK_SOUND);
	sm.addSound(GAME_OVER_SOUND);
	sm.addSound(NEXT_LEVEL_SOUND);
	sm.addSound(MOUSE_OVER_SOUND);

	sm.playSound(BG_SOUND, true);
}

bool GameManager::onFire(const string& eventName, const sf::Event& event) {

	//Checks the events
	if (Typeable::onFire(eventName, event)) {
		return true;
	} else if (eventName == ON_GAME_START) {
		_data._score = 0;
		_data._life = 3;
		_data._level = 1;
		_data._started = true;
		_data._isPaused = false;
		_data._gameOver = false;
		if (!_screen->loadLevel(1)) {
			_data._gameOver = true;
		}
	} else if (eventName == ON_GAME_EXIT) {
		_data._exit = true;
	} else if (eventName == ON_GAME_RESUME) {
		_data._isPaused = false;
		_screen->muteEvents(_data._isPaused);
		_hud->update(_data);
	} else if (eventName == ON_SOUND_STATE_CHANGED) {
		SoundsManager& sm = SoundsManager::getInstance();
		sm.mute(!sm.isMute());
		if (sm.isMute()) {
			sm.stopSound(BG_SOUND);
		} else {
			sm.playSound(BG_SOUND, true);
		}
	} else if (eventName == ON_NEW_RECORD_END) {
		_data._isNewRecord = false;
	}
	return false;
}

void GameManager::gameOver() {
	newRecord(_data._score);
	_data._gameOver = true;
}

void GameManager::newRecord(int score)
{
	auto best = ResourcesManager::getInstance().getBestScoreAsNumber();
	if (best < score)
	{
		_data._isNewRecord = true;
	}

}