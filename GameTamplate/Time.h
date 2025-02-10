#pragma once
static class Time
{
private:
	static float _timeScale;
	static float _deltaTime;
	static float _realTime;
public:
	static void updateTime(float value);
	static void setTimeScale(float value);
	static float getTimeScale();
	static float getDeltaTime();
	static float getRealTime();
};

