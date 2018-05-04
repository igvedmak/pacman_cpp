#include "Clickable.h"
#include "EventsManager.h"
#include "Constants.h"
#include "SoundsManager.h"

Clickable::Clickable() {
	//Listen to mouse events
	EventsManager::getInstance().subscribe(ON_MOUSE_DOWN, *this);
	EventsManager::getInstance().subscribe(ON_MOUSE_UP, *this);
	EventsManager::getInstance().subscribe(ON_MOUSE_MOVE, *this);
}

Clickable::~Clickable() {
	//Remove listen to mouse events
	EventsManager::getInstance().unsubscribe(ON_MOUSE_DOWN, *this);
	EventsManager::getInstance().unsubscribe(ON_MOUSE_UP, *this);
	EventsManager::getInstance().unsubscribe(ON_MOUSE_MOVE, *this);
}

bool Clickable::onFire(const string& eventName, const sf::Event& event) {
	if (_mute)
		return false;

	//Checks which event has fired
	if (eventName == ON_MOUSE_DOWN) {
		return mouseDown(event);
	} else if (eventName == ON_MOUSE_UP) {
		return mouseUp(event);
	} else if (eventName == ON_MOUSE_MOVE) {
		return mouseMove(event);
	}
	return false;
}

void Clickable::onMouseDown(const EventFunction& func) {
	_onMouseDownFunc = func;
}

void Clickable::onMouseMove(const EventFunction& func) {
	_onMouseMoveFunc = func;
}

void Clickable::onMouseUp(const EventFunction& func) {
	_onMouseUpFunc = func;
}

bool Clickable::mouseDown(const sf::Event& event) {
	//Checks if the mouse event is on the current object
	if (isContain({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
		if (_onMouseDownFunc != nullptr && !_onMouseDownFunc(ON_MOUSE_DOWN, event, *this)) {
			return false;
		}
		return true;
	}
	return false;
}

bool Clickable::mouseUp(const sf::Event& event) {
	//Checks if the mouse event is on the current object
	if (isContain({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
		if (_onMouseUpFunc != nullptr && !_onMouseUpFunc(ON_MOUSE_DOWN, event, *this)) {
			return false;
		}

		//Set to focused if not focused yet
		if (!_isFocused)
			_isFocused = true;
		return true;
	}
	//Set to no focused if focused
	if (_isFocused)
		_isFocused = false;
	return false;
}

bool Clickable::mouseMove(const sf::Event& event) {
	//Checks if the mouse event is on the current object
	if (isContain({ (float)event.mouseMove.x, (float)event.mouseMove.y })) {
		if (_onMouseMoveFunc != nullptr && !_onMouseMoveFunc(ON_MOUSE_DOWN, event, *this)) {
			return false;
		}
		if (!_isHovered)
			SoundsManager::getInstance().playSound(MOUSE_OVER_SOUND);
		_isHovered = true;
		return true;
	}
	_isHovered = false;
	return false;
}
