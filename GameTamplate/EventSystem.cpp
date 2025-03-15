#include "EventSystem.h"

Dictionary<string, vector<void (*)()>> EventSystem::_events = Dictionary<string, vector<void (*)()>>();

void EventSystem::addChannel(string channel) {
	if (!_events.containsKey(channel)) {
		_events.addItem(channel, vector<void (*)()>());
	}
}

void EventSystem::removeChannel(string channel) {
	if (_events.containsKey(channel)) {
		_events.removeItem(channel);
	}
}

void EventSystem::subscribeFunction(string channel, void (*function)()) {
	if (!_events.containsKey(channel)) {
		_events.addItem(channel, vector<void (*)()>());
	}

	vector<void (*)()> eventFunctions = _events.getValue(channel);
	eventFunctions.push_back(function);
	_events.setValue(channel, eventFunctions);
}

void EventSystem::unSubscribeFunction(string channel, void(*function)()) {
	vector<void (*)()> eventFunctions = _events.getValue(channel);

	eventFunctions.erase(remove(eventFunctions.begin(), eventFunctions.end(), function), eventFunctions.end());
}

void EventSystem::invokeChannel(string channel) {
	if (!_events.containsKey(channel)) {
		return;
	}

	vector<void (*)()> eventFunctions = _events.getValue(channel);

	for (void (*function)() : eventFunctions) {
		function();
	}
}
