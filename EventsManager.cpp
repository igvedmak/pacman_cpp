#include "EventsManager.h"
#include "EventSubscriber.h"
#include <utility>
#include <cstdarg>
#include "Constants.h"

EventsManager & EventsManager::getInstance() {
	static EventsManager instance;
	return instance;
}

bool EventsManager::subscribe(const string& eventName, EventSubscriber& subscriber) {
	auto subscriptionIt = find(eventName, subscriber);

	if (subscriptionIt == _subscribers.end()) {
		_subscribers.insert(std::make_pair(eventName, &subscriber));
		return true;
	}

	return false;
}

bool EventsManager::unsubscribe(const string& eventName, EventSubscriber& subscriber) {
	auto subscriptionIt = find(eventName, subscriber);

	if (subscriptionIt != _subscribers.end()) {
		_subscribers.erase(subscriptionIt);
		return true;
	}

	return false;
}

bool EventsManager::fireEvent(const string& eventName, const sf::Event& event) {
	auto subscribersByEventName = _subscribers.equal_range(eventName);

	//Fire all the events
	for (auto it = subscribersByEventName.first; it != subscribersByEventName.second; ++it) {
		if ((*it).second->onFire(eventName, event))
			break;
		
	}

	return true;
}

EventsMultiMap::iterator EventsManager::find(const string& eventName, EventSubscriber& subscriber) {
	auto subscribersByEventName = _subscribers.equal_range(eventName);

	for (auto it = subscribersByEventName.first; it != subscribersByEventName.second; ++it) {
		if ((*it).second == &subscriber) {
			return it;
		}
	}

	return _subscribers.end();
}
