#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class EventSubscriber;

using std::string;
using std::multimap;

typedef multimap<string, EventSubscriber *> EventsMultiMap;

//Manage all the events in the current game like click, typeing, etc.. 
class EventsManager
{
	public:
		//Singleton get instance
		static EventsManager& getInstance();
		//Subscribe to event
		bool subscribe(const string& eventName, EventSubscriber& subscriber);
		//Unsubscribe from event
		bool unsubscribe(const string& eventName, EventSubscriber& subscriber);
		//Fire the event by name and data
		bool fireEvent(const string& eventName, const sf::Event& event);

	protected:
		EventsMultiMap _subscribers;
		//Return the iterator of the event subscribe if exsits else return the _subscribers end iterator
		EventsMultiMap::iterator find(const string& eventName, EventSubscriber& subscriber);
};

