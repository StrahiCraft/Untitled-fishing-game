#pragma once
#include "Sprite.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class FishStats
{
private:
	Sprite* _fishSprite;

	float _weight;
	float _fishSpeed;
	float _captureRate;
	float _goalCircleSize;
	int _score;

	float _minWeight;
	float _maxWeight;

public:
	FishStats(string filePath);

	Sprite* getFishSprite();

	float getWeight();
	float getFishSpeed();
	float getCaptureRate();
	float getGoalCircleSize();
	int getScore();
};

