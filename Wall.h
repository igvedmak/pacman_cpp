#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
	public:
		//Constructor that get color, pos and size
		Wall(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size);
		~Wall();
};

