#include "Ring.h"

Ring::Ring(glm::vec2 position, glm::vec2 velocity) : Pickup(position, velocity) {
	_sprite = new Sprite("Sprites/ring.png", glm::vec2(35), 1, glm::vec2(8, 1), true);
	_sprite->setAnimationDelay(0.05f);
}

void Ring::update() {
	if (!_active) {
		return;
	}
	_sprite->update(Time::getDeltaTime());
	move();
}

void Ring::render() {
	if (!_active) {
		return;
	}
	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0);
	glTranslatef(-17, -17, 0);

	_sprite->render();

	glPopMatrix();
}

void Ring::onPickup() {
	if (!_active) {
		return;
	}
	_active = false;
	ScoreManager::increaseScore(1);
	AudioManager::playSound("ring");
}
