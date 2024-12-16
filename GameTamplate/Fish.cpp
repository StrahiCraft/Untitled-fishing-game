#include "Fish.h"

Fish::Fish(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, glm::vec2 windowSize) : GameObject(pos, vel, spr) {
	_windowSize = windowSize;
	_goalCircle = primitive::createCircle(glm::vec3(0), glm::vec3(0.25f), 320);
	_currentFishingCircle = primitive::createCircle(glm::vec3(0), glm::vec3(1), 32);
	resetFish();
}

float Fish::getGoalCircleSize()
{
	return _goalCircleSize;
}

void Fish::update(float dt) {
	if (!_active) {
		return;
	}

	if (_currentCircleSize >= _goalCircleSize) {
		resetFish();

		// go to second minigame

		return;
	}

	if (glm::distance(_position, _destination) < 30) {
		randomizeDestination();
		return;
	}


	_position += _velocity * dt * _fishSpeed;
}

void Fish::render() {
	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0.0f);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glScalef(_scale.x, _scale.y, 1.0f);

	if (!_active) {
		return;
	}
	
	_primitive = _goalCircle;
	drawCircle(_goalCircleSize);
	_primitive = _currentFishingCircle;
	drawCircle(_currentCircleSize);

	glTranslatef(-_sprite->getSize().x / 2, -_sprite->getSize().y / 2, 0.0f);

	getSprite()->render();

	glPopMatrix();
}

void Fish::randomizePosition() {
	_position = glm::vec2(rand() % (int)_windowSize.x, rand() % (int)_windowSize.y);
}

void Fish::randomizeDestination() {
	_destination = glm::vec2(rand() % (int)_windowSize.x, rand() % (int)_windowSize.y);
	_velocity = glm::normalize(_destination - _position);
}

void Fish::resetFish() {
	randomizePosition();
	randomizeDestination();
	_currentCircleSize = 0;
	_goalCircleSize = rand() % 150 + 50;
	_captureRate = rand() % 50 + 25;
	_fishSpeed = rand() % 200 + 100;
}

void Fish::increaseCaptureScore(float dt) {
	_currentCircleSize += dt * _captureRate;

	if (_currentCircleSize <= 0) {
		_currentCircleSize = 0;
	}
}
