#pragma once
#include "Figure.h"

class Pacman : public Figure
{
	public:
		//Constructor that get color, pos and size
		Pacman(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size);
		~Pacman();
};

