#include "EventSubscriber.h"


EventSubscriber::EventSubscriber() {}

EventSubscriber::~EventSubscriber() {}

void EventSubscriber::muteEvents(bool mute) {
	_mute = mute;
}
