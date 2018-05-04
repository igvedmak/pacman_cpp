#pragma once
#include "DrawableObject.h"
#include "Typeable.h"
#include "Clickable.h"

class TextInputBox : public DrawableObject, public Typeable
{
public:
	TextInputBox(sf::Vector2<float> size, sf::Vector2<float> pos);
	~TextInputBox();
	//Draw the object on the window (pure virtual)
	virtual void draw(sf::RenderWindow& window) const;
	//Return the center of the object (pure virtual)
	virtual sf::Vector2f getCenter() const;
	//When a key pressed
	virtual bool keyPressed(const sf::Event& event);
	//Override pure virtual textEntered of Typeable
	bool textEntered(const sf::Event& event);
	//Set input box position
	void setPos(sf::Vector2f pos);
	//Set input box size
	void setSize(sf::Vector2f size);
	//Gets the string that was entered to the box
	string getName();
	//Check if the box is close
	bool isClosed();
	//Mute events 
	void setMute(bool m);


protected:
	sf::Font& _font;
	void addChar(char c);
	void removeLastChar();
	sf::Vector2<float> _size;
	string _text;
	string _nameEnterd;
	bool _boxClosed;
	sf::Vector2<float> _pos;
	sf::Vector2<float> _paddingTL;
	sf::Vector2<float> _paddingBR;
	void setPadding(float top, float bottom, float left, float right);
};