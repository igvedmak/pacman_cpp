#pragma once
#include "EventSubscriber.h"
#include <functional>

class EventsManager;


class Typeable : public EventSubscriber
{
	public:
		//Constructor
		Typeable();
		virtual ~Typeable();
		//Override pure virtual onFire EventSubscriber
		bool onFire(const string& eventName, const sf::Event& event);

	protected:
		//When a key pressed
		virtual bool keyPressed(const sf::Event& event) = 0;
		//When a text entered
		virtual bool textEntered(const sf::Event& event) = 0;
};

