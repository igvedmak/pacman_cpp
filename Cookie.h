#pragma once
#include "GameObject.h"

class Cookie : public GameObject
{
	public:
		//Constructor that get color, pos and size
		Cookie(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size);
		~Cookie();
		//Sets the cookie type
		void setCookieType(CookieType type);
		//Return the cookie type
		CookieType getCookieType();
		//Override virtual intersects of GameObject
		bool intersects(const sf::FloatRect& rect);
	private:
		CookieType _type;
};