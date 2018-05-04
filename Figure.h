#pragma once
#include "Moveable.h"
#include "GameObject.h"

class Figure : public GameObject, public Moveable
{
	public:
		//Same as GameObejct constructor
		using GameObject::GameObject;
		virtual ~Figure() = 0;
		//Override pure virtual move of Moveable
		void move();
		//Reset the object to start position
		void resetToStartPosition();
		//Fix the position if the object close to input position
		void fixPosition(const sf::Vector2f& gridPos);
	protected:
		//Rotate the sprite by the direction
		void rotateSprite();
		//Get the next position by the direction
		sf::Vector2f getPositionByDirection(Direction dir) const;
};