#include "Wall.h"

Wall::Wall(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size)
	: GameObject(WallTexture, color, pos, size) {
}

Wall::~Wall() {}