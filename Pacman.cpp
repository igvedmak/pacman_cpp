#include "Pacman.h"



Pacman::Pacman(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Figure(PacmanTexture, color, pos, size) {
	_canAccelerate = true;
}

Pacman::~Pacman() {}