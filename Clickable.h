#pragma once
#include <SFML/Graphics.hpp>
#include "EventSubscriber.h"
#include <functional>
#include <SFML/Audio.hpp>

class EventsManager;

class Clickable : public EventSubscriber
{
	public:
		//Constructor
		Clickable();
		virtual ~Clickable();
		//Override pure virtual onFire EventSubscriber
		bool onFire(const string& eventName, const sf::Event& event);
		//Set the calback when the mouse down 
		void onMouseDown(const EventFunction& func);
		//Set the calback when the mouse move 
		void onMouseMove(const EventFunction& func);
		//Set the calback when the mouse realesed 
		void onMouseUp(const EventFunction& func);

	protected:
		bool _isFocused = false;
		bool _isHovered = false;

		EventFunction _onMouseDownFunc;
		EventFunction _onMouseUpFunc;
		EventFunction _onMouseMoveFunc;

		//Return if the object contains the pos
		virtual bool isContain(const sf::Vector2f& pos) const = 0;
		//When the mouse pressed
		virtual bool mouseDown(const sf::Event& event);
		//When the mouse released
		virtual bool mouseUp(const sf::Event& event);
		//When the mouse move
		virtual bool mouseMove(const sf::Event& event);
};

