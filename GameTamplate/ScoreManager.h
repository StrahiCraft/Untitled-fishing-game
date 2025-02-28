#pragma once
#include "TextRenderer.h"
#include <fstream>
#include <string>

static class ScoreManager
{
private:
	static int _score;
	static TextRenderer* _scoreText;
	static vector<int> _highScores;
public:
	static void init();
	static void render();
	static int getScore();
	static void setScore(int newValue);
	static void increaseScore(int value);
	static void addNewScore(int score); // this can be changed to support scores that show more info about the run
	static vector<int> getHighScores();
private:
	static void sortScores();
};

