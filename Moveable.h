#pragma once
#include "EventSubscriber.h"
#include <functional>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Moveable : public EventSubscriber
{
	public:
		//Constructor
		Moveable();
		virtual ~Moveable();
		//Override pure virtual onFire EventSubscriber
		bool onFire(const string& eventName, const sf::Event& event);
		//Set the calback when the object need to move 
		void onMove(std::function<bool(const string& eventName, const sf::Event& event, EventSubscriber& obejct)> func);
		//Set the calback when the object need to know if it can move 
		void canMove(std::function<bool(Moveable& obejct, Direction direction)> func);
		//When the object need to move
		virtual void move() = 0;
		//Chenge the direction of the object
		virtual void moveDirection(Direction direction);
		//Get the current moving direction
		Direction getMovingDirection() const;
		//Set the factor of speed with timeout
		void setSpeedFactor(double factor, unsigned int secTime);
		//Get the current speed (speed * factor)
		double getSpeed() const;

	protected:
		std::function<bool(const string& eventName, const sf::Event& event, EventSubscriber& obejct)> _onMoveFunc;
		std::function<bool(Moveable& obejct, Direction direction) > _canMoveFunc;
		int _defaultSpeed;
		int _currentSpeed;
		bool _canAccelerate = false;
		double _factor = 1;
		unsigned int _secFactorTime = 0;
		float _lastFactorSecTime = 0;
		float _lastMoveSecTime = 0;
		Direction _direction = None;
		Direction _lastDirection = None;
};

