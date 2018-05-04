#include "GameObject.h"
#include "ResourcesManager.h"

GameObject::GameObject(TextureType spriteIndex, TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size)
	: _sprite(ResourcesManager::getInstance().getTexture(GAME_TEXTURES)), _textureType(spriteIndex) , _size(size) {
	//Set the sprite properties
	_sprite.setTextureRect(sf::IntRect(color * SPRITE_SIZE, spriteIndex * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE));
	_sprite.setScale(size.x / SPRITE_SIZE, size.y / SPRITE_SIZE);
	_sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
	_sprite.setPosition({ pos.x + size.x / 2, pos.y + size.y / 2 });

	_startPos = pos;
}

GameObject::~GameObject() {}

sf::Vector2<float> GameObject::getCenter() const {
	return { _sprite.getGlobalBounds().left + (_sprite.getGlobalBounds().width / 2),
			 _sprite.getGlobalBounds().top + (_sprite.getGlobalBounds().height / 2) };
}

void GameObject::draw(sf::RenderWindow & window) const {
	window.draw(_sprite);
}

TextureType GameObject::getTextureType() const {
	return _textureType;
}

sf::FloatRect GameObject::getBoundingRect() const {
	return _sprite.getGlobalBounds();
}

bool GameObject::intersects(const sf::FloatRect& rect) const {
	sf::FloatRect rect2 = getBoundingRect();
	//Check if the rectangles are intersects exclude borders
	return std::abs(rect.left - rect2.left) * 2 < (rect.width + rect2.width - 1) &&
		   std::abs(rect.top - rect2.top) * 2 < (rect.height + rect2.height - 1);
}

bool GameObject::conatains(const sf::Vector2f& pos) const {
	sf::FloatRect rect2 = getBoundingRect();
	float minX = std::min(rect2.left, rect2.left + rect2.width);
	float maxX = std::max(rect2.left, rect2.left + rect2.width);
	float minY = std::min(rect2.top, rect2.top + rect2.height);
	float maxY = std::max(rect2.top, rect2.top + rect2.height);

	if (pos.x >= minX && pos.x <= maxX && pos.y >= minY && pos.y <= maxY) {
		return true;
	}
	
	return false;
}
