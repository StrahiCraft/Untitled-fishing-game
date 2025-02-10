#include "Time.h"

float Time::_timeScale = 1;
float Time::_deltaTime;
float Time::_realTime;

void Time::updateTime(float value) {
	_realTime = value;
	_deltaTime = value * _timeScale;
}

void Time::setTimeScale(float value) {
	_timeScale = value;
}

float Time::getTimeScale() {
	return _timeScale;
}

float Time::getDeltaTime()
{
	return _deltaTime;
}

float Time::getRealTime()
{
	return _realTime;
}
