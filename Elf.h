#pragma once
#include "Figure.h"

class Elf : public Figure
{
	public:
		//Constructor that get color, pos and size
		Elf(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size);
		~Elf();
		//Override pure virtual move of Moveable
		void move();
	private:
		bool _isSmart;
		float _lastDirectionChange = 0;
};