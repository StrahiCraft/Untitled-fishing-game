#include "BurstStream.h"

BurstStream::BurstStream(glm::vec2 position, glm::vec2 velocity) : Pickup(position, velocity) {
	_sprite = new Sprite("Sprites/burstStream.png", glm::vec2(64), 1, glm::vec2(1), true);
	_burstStreamEffect = new Sprite("Sprites/burstStreamEffect.png", glm::vec2(396, 1170), 1, glm::vec2(1), true);
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
		_rotation += Time::getDeltaTime() * 60;
		EventSystem::invokeChannel("BurstStream");
		return;
	}

	move();
}

void BurstStream::render() {
	if (!_active) {
		return;
	}

	glPushMatrix();
	glTranslatef(-32, -32, 0);
	glTranslatef(_position.x, _position.y, 0);
	glRotatef(_rotation, 0, 0, 1);

	_sprite->render();

	glPopMatrix();
}

void BurstStream::onPickup() {
	if (_animationStarted) {
		return;
	}

	_animationStarted = true;
	
	setPosition(glm::vec2(-200, 400));
	_rotation = -135;
	_sprite = _burstStreamEffect;

	AudioManager::playSound("BurstStream");
}
