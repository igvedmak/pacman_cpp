#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "Clickable.h"

class RectButton : public DrawableObject, public Clickable
{
	public:
		//Constructor that get pos, size, color, colorOnFocused, font, the text, the event when clicked
		RectButton(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Color color, sf::Color _colorOnFocused, sf::Font& font, const string& text, const string& eventName);
		~RectButton();

		//Return the event of the button
		string getEventName();
		//Override pure virtual draw of Drawable
		void draw(sf::RenderWindow & window) const;
		//Override pure virtual getCenter of Drawable
		sf::Vector2f getCenter() const;
		//Override pure virtual isContain of Clickable
		bool isContain(const sf::Vector2f& pos) const;
		//Return the text of the button
		string getText();
		//Override virtual mouseMove of Clickable
		virtual bool mouseMove(const sf::Event& event);
		
	private:
		sf::Color _color;
		sf::Color _colorOnFocused;
		sf::RectangleShape _rect;
		sf::Text _text;
		string _eventName;
		sf::RenderTexture _renderTexture;
		sf::Sprite _sprite;
		//Upadte the textbox
		void updateTextBox();
};

