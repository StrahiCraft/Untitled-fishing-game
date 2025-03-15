#include "BurstStream.h"

BurstStream::BurstStream(glm::vec2 position, glm::vec2 velocity) : Pickup(position, velocity) {
	_sprite = new Sprite("Sprites/burstStream.png", glm::vec2(64), 1, glm::vec2(1), true);
}

void BurstStream::update() {
	if (!_active) {
		return;
	}

	if (_animationTimer >= 2.5f) {
		_active = false;
		return;
	}

	if (_animationStarted) {
		_animationTimer += Time::getDeltaTime();
		EventSystem::invokeChannel("BurstStream");
		return;
	}

	move();
}

void BurstStream::render() {
	if (!_active) {
		return;
	}

	if (_animationStarted) {
		return;
	}

	glPushMatrix();
	glTranslatef(_position.x, _position.y, 0);
	glTranslatef(-32, -32, 0);

	_sprite->render();

	glPopMatrix();
}

void BurstStream::onPickup() {
	_animationStarted = true;
	
	setPosition(glm::vec2(1000, 400));

	AudioManager::playSound("BurstStream");
}
