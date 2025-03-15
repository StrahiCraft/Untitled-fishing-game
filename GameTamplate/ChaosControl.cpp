#include "ChaosControl.h"

ChaosControl::ChaosControl(glm::vec2 position, glm::vec2 velocity) : Pickup(position, velocity) {
	_sprite = new Sprite("Sprites/chaosEmerald.png", glm::vec2(64), 1, glm::vec2(1), true);
	_chaosControlOverlay = new Sprite("Sprites/chaosControl.png", glm::vec2(1), 1, glm::vec2(1), true);
}

void ChaosControl::update() {
	if (!_active) {
		return;
	}

	if (_timeStopped) {
		_timeStopTimer += Time::getRealTime();
	}

	if (_timeStopTimer >= 5) {
		Time::setTimeScale(1);
		_active = false;
		return;
	}

	move();
}

void ChaosControl::render() {
	if (!_active) {
		return;
	}

	if (_timeStopped) {
		glPushMatrix();

		glScalef(1000, 1000, 1);

		_chaosControlOverlay->render();
		
		glPopMatrix();
		return;
	}

	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0);
	glTranslatef(-32, -32, 0);

	_sprite->render();

	glPopMatrix();
}

void ChaosControl::onPickup() {
	_velocity = glm::vec2(0);
	_position = glm::vec2(-150);
	_timeStopped = true;
	Time::setTimeScale(0);
	AudioManager::playSound("chaosControl");
}

ChaosControl::~ChaosControl() {
	Time::setTimeScale(1);
}
