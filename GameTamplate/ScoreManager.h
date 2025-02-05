#pragma once
#include "TextRenderer.h"
#include <string>

static class ScoreManager
{
private:
	static int _score;
	static TextRenderer* _scoreText;
public:
	static void init();
	static void render();
	static int getScore();
	static void setScore(int newValue);
	static void increaseScore(int value);
};

