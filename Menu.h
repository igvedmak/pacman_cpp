#pragma once
#include "DrawableObject.h"
#include "EventSubscriber.h"
#include "RectButton.h"
#include <memory>
#include <functional>
#include <string>



class Menu : public DrawableObject
{
	public:
		//Constructor that get size
		Menu(const sf::Vector2f& size);
		~Menu();
		sf::Vector2f getCenter() const;
		//Override pure virtual draw of Drawable
		void draw(sf::RenderWindow& window) const;
		//Call back when button clicked
		bool menuSelect(const string& eventName, const sf::Event& event, EventSubscriber& obejct);
		//Toggle menu by input
		void showMenu(bool show, bool isPaused);
		//Mute the menu events
		void mute(bool isMute);

	private:
		sf::RectangleShape _rect;
		std::vector<std::unique_ptr<RectButton>> _buttons;
		bool _show = true;
		bool _isPaused = false;;
		
};

