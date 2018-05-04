#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Graphics.hpp>

using std::string;

class EventSubscriber {
	public:
		EventSubscriber();
		virtual ~EventSubscriber();
		//When listened event has fired
		virtual bool onFire(const string& eventName, const sf::Event& event) = 0;
		//Mute the events of the current object
		virtual void muteEvents(bool mute);

	protected:
		bool _mute = false;
};

typedef std::function<bool(const string& eventName, const sf::Event& event, EventSubscriber& obejct)> EventFunction;