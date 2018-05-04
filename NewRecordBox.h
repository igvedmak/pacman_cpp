#pragma once
#include "DrawableObject.h"
#include <SFML/Graphics.hpp>
#include "TextInputBox.h"

class NewRecordBox : public DrawableObject
{
public:
	NewRecordBox(sf::Vector2f winSize);
	~NewRecordBox();
	//Gets the new record and updates it.
	void update(int newRecord);
	//Override pure virtual draw of Drawable
	void draw(sf::RenderWindow& window) const;
	sf::Vector2f getCenter() const;
	//Check if the input box is closed
	bool isInputClosed();
	//Mute the input box
	void setMute(bool m);

private:
	sf::RectangleShape rect;
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
	sf::Text text4;
	TextInputBox _textInput ;
};

