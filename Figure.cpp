#include "Figure.h"
#include "GameClock.h"

Figure::~Figure() {}

void Figure::move() {
	//Checks if time of speed factor passed
	if(_secFactorTime != 0 && GameClock::getInstance().isTimePassed(_lastFactorSecTime, (float)_secFactorTime)) {
		_factor = 1;
		_secFactorTime = 0;
	}

	//Checks if the time to move is not passed
	if (!GameClock::getInstance().isTimePassed(_lastMoveSecTime, (1 / ((float)_currentSpeed * (float)_factor))))
		return;

	//Set the current time as the last time to next move
	_lastMoveSecTime = GameClock::getInstance().getElapsedTime();

	Direction dir = None;

	if (_canMoveFunc != nullptr && _canMoveFunc(*this, _direction)) {
		//If the object can move to new direction
		rotateSprite();
		dir = _direction;
		_lastDirection = _direction;
	} else if (_canMoveFunc != nullptr && _canMoveFunc(*this, _lastDirection)) {
		//If the object can move to last direction
		dir = _lastDirection;
	} else {
		//The object cant move
		_lastDirection = _direction = None;
		//_currentSpeed = _defaultSpeed;
	}

	if (dir != None) {
		_sprite.setPosition(getPositionByDirection(dir));
	}
}

void Figure::resetToStartPosition() {
	_sprite.setRotation(0);
	_sprite.setPosition({ _startPos.x + _size.x / 2, _startPos.y + _size.y / 2 });
	_lastDirection = _direction = None;
}

void Figure::rotateSprite() {
	//Rotate sprite by direction
	switch (_direction)
	{
		case Up:
			_sprite.setRotation(180);
			break;
		case Down:
			_sprite.setRotation(0);
			break;
		case Left:
			_sprite.setRotation(90);
			break;
		case Right:
			_sprite.setRotation(270);
			break;
	}
}

sf::Vector2f Figure::getPositionByDirection(Direction dir) const {
	//Get nxt pos by direction
	sf::Vector2f pos = _sprite.getPosition();

	switch (_lastDirection) {
		case Up:
			pos.y -= 1;
			break;
		case Down:
			pos.y += 1;
			break;
		case Left:
			pos.x -= 1;
			break;
		case Right:
			pos.x += 1;
			break;
	}

	return pos;
}


void Figure::fixPosition(const sf::Vector2f& gridPos) {
	//If th object is very close to center of the grid cell adjust it to center
	if ((std::abs(gridPos.x - getCenter().x) >= 0.5f && std::abs(gridPos.x - getCenter().x) < 1.0f) ||
		(std::abs(gridPos.y - getCenter().y) >= 0.5f && std::abs(gridPos.y - getCenter().y) < 1.0f)) {
		_sprite.setPosition({
			gridPos.x,
			gridPos.y
		});
	}
}