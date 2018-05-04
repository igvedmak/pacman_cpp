#include "Typeable.h"
#include "EventsManager.h"
#include "Constants.h"

Typeable::Typeable() {
	//Listen to mouse events
	EventsManager::getInstance().subscribe(ON_KEY_PRESSED, *this);
	EventsManager::getInstance().subscribe(ON_TEXT_ENTERED, *this);

}

Typeable::~Typeable() {
	//Remove listen to mouse events
	EventsManager::getInstance().unsubscribe(ON_KEY_PRESSED, *this);
	EventsManager::getInstance().unsubscribe(ON_TEXT_ENTERED, *this);
}

bool Typeable::onFire(const string& eventName, const sf::Event& event) {
	if (_mute)
		return false;

	if (eventName == ON_KEY_PRESSED) {
		return keyPressed(event);
	} else if (eventName == ON_TEXT_ENTERED) {
		return textEntered(event);
	}

	return false;
}