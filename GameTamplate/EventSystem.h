#pragma once
#include "Dictionary.h"
#include "Dictionary.cpp"
#include <iostream>

static class EventSystem
{
private:
	static Dictionary<string, vector<void (*)()>> _events;

public:
	static void subscribeFunction(string channel, void (*function)());
	static void invokeChannel(string channel);

	EventSystem() = delete;
};

