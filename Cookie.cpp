#include "Cookie.h"

Cookie::Cookie(TextureColor color, const sf::Vector2f& pos, const sf::Vector2f& size)
	: GameObject(CookieTexture, color, pos, size) {
	_type = (CookieType)(color);
}

Cookie::~Cookie() {}

void Cookie::setCookieType(CookieType type) {
	_type = type;
}

CookieType Cookie::getCookieType() {
	return _type;
}

bool Cookie::intersects(const sf::FloatRect& rect) {
	auto myrect = getBoundingRect();
	auto center = getCenter();

	//Checks for middle intersects with cookie
	if (std::abs(rect.left + (rect.width / 2) - center.x) < 2 &&
		std::abs(rect.top + rect.height - center.y) < 2) {
		return true;
	} else if (std::abs(rect.left + (rect.width / 2) - center.x) < 2 &&
				std::abs(rect.top - center.y) < 3) {
		return true;
	} else if (std::abs(rect.top + (rect.height / 2) - center.y) < 2 &&
			   std::abs(rect.left + rect.width - center.x) < 2) {
		return true;
	} else if (std::abs(rect.top + (rect.height / 2) - center.y) < 2 &&
				std::abs(rect.left - center.x) < 3) {
		return true;
	}

	return false;
}
