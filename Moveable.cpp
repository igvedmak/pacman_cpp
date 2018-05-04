#include "Moveable.h"
#include "EventsManager.h"
#include "Constants.h"
#include "GameClock.h"


Moveable::Moveable() {
	//Listen to move events
	EventsManager::getInstance().subscribe(ON_MOVE, *this);
	_currentSpeed = _defaultSpeed = DEFAULT_SPEED;
}

Moveable::~Moveable() {
	//Remove listen to move events
	EventsManager::getInstance().unsubscribe(ON_MOVE, *this);
}

bool Moveable::onFire(const string& eventName, const sf::Event& event) {
	if (_mute)
		return false;

	//Checks which event has fired
	if (eventName == ON_MOVE) {
		move();
	}

	return false;
}

void Moveable::onMove(std::function<bool(const string& eventName, const sf::Event& event, EventSubscriber& obejct)> func) {
	_onMoveFunc = func;
}

void Moveable::canMove(std::function<bool(Moveable& obejct, Direction direction)> func)  {
	_canMoveFunc = func;
}

void Moveable::moveDirection(Direction direction) {
	if (_lastDirection == Up && direction == Down ||
		_lastDirection == Down && direction == Up ||
		_lastDirection == Right && direction == Left ||
		_lastDirection == Left && direction == Right) {
		//If the new direction is the oppsite of the last direction
		_lastDirection = _direction = None;
		_currentSpeed = _defaultSpeed;
	} else {
		//Checks if can accelerate
		if (_canAccelerate && _lastDirection == direction) {
			if (_currentSpeed < MAX_SPEED)
				_currentSpeed += DEFAULT_SPEED;
		}
		_direction = direction;
	}
	
}

Direction Moveable::getMovingDirection() const {
	return _lastDirection;
}

void Moveable::setSpeedFactor(double factor, unsigned int secTime) {
	_factor *= factor;
	_lastFactorSecTime =  GameClock::getInstance().getElapsedTime();
	_secFactorTime = secTime;
}

double Moveable::getSpeed() const {
	return _currentSpeed * _factor;
}