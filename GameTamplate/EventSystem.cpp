#include "EventSystem.h"

Dictionary<string, vector<void (*)()>> EventSystem::_events = Dictionary<string, vector<void (*)()>>();

void EventSystem::subscribeFunction(string channel, void (*function)()) {
	if (!_events.containsKey(channel)) {
		_events.addItem(channel, vector<void (*)()>());
	}

	vector<void (*)()> eventFunctions = _events.getValue(channel);
	eventFunctions.push_back(function);
	_events.setValue(channel, eventFunctions);
}

void EventSystem::invokeChannel(string channel) {
	vector<void (*)()> eventFunctions = _events.getValue(channel);
	_events.setValue(channel, eventFunctions);

	for (void (*function)() : eventFunctions) {
		function();
	}
}
