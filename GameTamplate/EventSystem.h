#pragma once
#include "Dictionary.h"
#include "Dictionary.cpp"
#include <iostream>

static class EventSystem
{
private:
	static Dictionary<string, vector<void (*)()>> _events;

public:
	static void addChannel(string channel);
	static void removeChannel(string channel);
	static void subscribeFunction(string channel, void (*function)());
	static void unSubscribeFunction(string channel, void (*function)());
	static void invokeChannel(string channel);

	EventSystem() = delete;
};

