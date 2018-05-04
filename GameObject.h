#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "Moveable.h"
#include "Constants.h"

class GameObject : public DrawableObject {
	public:
		//Constructor that get texturetype, color, pos and size
		GameObject(TextureType spriteIndex, TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size);
		virtual ~GameObject() = 0;

		//Override pure virtual getCenter of Drawable
		sf::Vector2<float> getCenter() const;
		//Override pure virtual draw of Drawable
		void draw(sf::RenderWindow& window) const;
		//Return the texture type of the object
		TextureType getTextureType() const;
		//Return the bounding rect of the object
		sf::FloatRect getBoundingRect() const;
		//Return if the current sprite rect intersects with input rect
		virtual bool intersects(const sf::FloatRect& rect) const;
		//Return if the current sprite rect contain the input pos 
		bool conatains(const sf::Vector2f& pos) const;

	protected:
		sf::Sprite _sprite;
		TextureType _textureType;
		sf::Vector2f _startPos;
		sf::Vector2f _size;
};

