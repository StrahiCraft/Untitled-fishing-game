#include "Fish.h"

Fish::Fish(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, glm::vec2 windowSize) : GameObject(pos, vel, spr) {
	_windowSize = windowSize;
	_goalCircle = primitive::createCircle(glm::vec3(0), glm::vec3(0.25f), 320);
	_currentFishingCircle = primitive::createCircle(glm::vec3(0), glm::vec3(1), 32);
}

FishStats Fish::getStats()
{
	return *_fishStats;
}

float Fish::getGoalCircleSize()
{
	return _fishStats->getGoalCircleSize();
}

int Fish::getScore()
{
	return _fishStats->getScore();
}

float Fish::getWeight()
{
	return _fishStats->getWeight();
}

string Fish::getName()
{
	return _fishStats->getName();
}

string Fish::getDescription()
{
	return _fishStats->getDescription();
}

void Fish::update() {
	if (!_active) {
		return;
	}

	if (_reelingIn) {
		return;
	}

	if(_position.x < -50 || _position.x > 850 ||
		_position.y < -50 || _position.y > 850) {
		randomizeDestination();
	}

	if (_velocity.x < 0) {
		_sprite->setSpriteFlip(glm::vec2(0, 1));
	}
	else {
		_sprite->setSpriteFlip(glm::vec2(0));
	}

	setRotation(getVelocityAngle() + 90);

	if (_currentCircleSize >= _fishStats->getGoalCircleSize()) {
		EventSystem::invokeChannel("ReelIn");
		_reelingIn = true;
		return;
	}

	if (glm::distance(_position, _destination) < 30) {
		randomizeDestination();
		return;
	}

	_position += _velocity * Time::getDeltaTime() * _fishStats->getFishSpeed();
}

void Fish::render() {
	if (!_active) {
		return;
	}

	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0.0f);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glScalef(_scale.x, _scale.y, 1.0f);

	if (!_reelingIn) {
		_primitive = _goalCircle;
		drawCircle(_fishStats->getGoalCircleSize());
		_primitive = _currentFishingCircle;
		drawCircle(_currentCircleSize);
	}

	glTranslatef(-_sprite->getSize().x / 2, -_sprite->getSize().y / 2, 0.0f);

	getSprite()->render();

	glPopMatrix();
}

void Fish::randomizePosition() {
	setPosition(glm::vec2(rand() % (int)_windowSize.x, rand() % (int)_windowSize.y));
}

void Fish::randomizeDestination() {
	_destination = glm::vec2(rand() % (int)_windowSize.x, rand() % (int)_windowSize.y);
	_velocity = glm::normalize(_destination - _position);
}

void Fish::resetFish(string statsFilePath) {
	_reelingIn = false;

	randomizePosition();
	randomizeDestination();
	_currentCircleSize = 0;
	_fishStats = new FishStats(statsFilePath);
	setSprite(_fishStats->getFishSprite());
}

void Fish::increaseCaptureScore(int multiplier) {
	_currentCircleSize += Time::getRealTime() * _fishStats->getCaptureRate() * multiplier;

	if (_currentCircleSize <= 0) {
		_currentCircleSize = 0;
		return;
	}
}
