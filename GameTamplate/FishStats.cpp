#include "FishStats.h"

FishStats::FishStats(string filePath) {
	if (filePath == "") {
		return;
	}
	ifstream file(filePath);

	string spriteFilePath;
	file >> spriteFilePath;

	file >> _minWeight;
	file >> _maxWeight;
	_weight = _minWeight + rand() % (int)(_maxWeight - _minWeight);
	float _weightMultiplier = (_weight - _minWeight) / (_maxWeight - _minWeight);

	file >> _fishSpeed;
	_fishSpeed *= (1.0f - 0.5f * _weightMultiplier);

	file >> _captureRate;
	_captureRate *= (1.0f - 0.5f * _weightMultiplier);

	file >> _goalCircleSize;
	_goalCircleSize *= (0.5f + 0.5f * _weightMultiplier);

	file >> _score;
	_score *= (1 + 1 * _weightMultiplier);
	
	_fishSprite = new Sprite(spriteFilePath.c_str(), glm::vec2(64, 32) * (1.0f + 1.0f * _weightMultiplier), 1, glm::vec2(1), true);
	
	file >> _fishName;

	file.close();
}

Sprite* FishStats::getFishSprite() {
	return _fishSprite;
}

float FishStats::getWeight() {
	return _weight;
}

float FishStats::getFishSpeed() {
	return _fishSpeed;
}

float FishStats::getCaptureRate() {
	return _captureRate;
}

float FishStats::getGoalCircleSize() {
	return _goalCircleSize;
}

int FishStats::getScore()
{
	return _score;
}

string FishStats::getName()
{
	return _fishName;
}