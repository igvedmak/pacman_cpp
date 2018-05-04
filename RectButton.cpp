#include "RectButton.h"
#include <string>
using std::string;

RectButton::RectButton(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Color color, sf::Color colorOnFocused, sf::Font& font, const string& text, const string& eventName)
	: _rect(size), _text(text, font, (unsigned int)size.y - 10), _color(color), _colorOnFocused(colorOnFocused), _eventName(eventName) {
	
	//Set rect properties
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::Transparent);
	_rect.setOrigin(size.x / 2, size.y / 2);

	float inner_height = (size.y - 5);
	float inner_width = (size.x - 5);

	//Set text properties
	_text.setPosition((inner_width - _text.getLocalBounds().width) / 2.0f,
					  (inner_height - _text.getLocalBounds().height) / 2.0f);
	_text.setOrigin(_text.getLocalBounds().left, _text.getLocalBounds().top);

	_text.setOutlineColor(sf::Color::Green);
	_text.setOutlineThickness(2);

	updateTextBox();
}

RectButton::~RectButton() {}

string RectButton::getEventName() {
	return _eventName;
}

void RectButton::draw(sf::RenderWindow & window) const {
	//Draw the bounding rect and the sprite on the window
	window.draw(_rect);
	window.draw(_sprite);
}

sf::Vector2<float> RectButton::getCenter() const {
	return { _rect.getGlobalBounds().left + _rect.getGlobalBounds().width / 2,
			 _rect.getGlobalBounds().top + _rect.getGlobalBounds().height / 2 };
}

bool RectButton::isContain(const sf::Vector2f& pos) const {
	if (pos.x >= _rect.getPosition().x - _rect.getOrigin().x && pos.x <= _rect.getPosition().x + _rect.getSize().x - _rect.getOrigin().x &&
		pos.y >= _rect.getPosition().y - _rect.getOrigin().y && pos.y <= _rect.getPosition().y + _rect.getSize().y - _rect.getOrigin().y)
		return true;
	return false;
}

string RectButton::getText() {
	return _text.getString();
}

bool RectButton::mouseMove(const sf::Event& event) {
	if (Clickable::mouseMove(event)) {
		_text.setFillColor(_colorOnFocused);
		updateTextBox();
		return true;
	}
	_text.setFillColor(_color);
	updateTextBox();
	return false;
}

void RectButton::updateTextBox() {
	float inner_height = (_rect.getSize().y - 5);
	float inner_width = (_rect.getSize().x - 5);
	//Set new render textrue to avoid overflow of text
	_renderTexture.create((int)inner_width, (int)inner_height);
	_renderTexture.clear(sf::Color::Transparent);

	//Draw the text on the render texture
	_renderTexture.draw(_text);
	_renderTexture.display();

	//Convert the render texture to sprite
	_sprite.setTexture(_renderTexture.getTexture());
	_sprite.setPosition(_rect.getPosition().x + 5, _rect.getPosition().y + 5);
	_sprite.setOrigin(_rect.getSize().x / 2, _rect.getSize().y / 2);
}
