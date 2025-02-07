#include "Pickup.h"

Pickup::Pickup(glm::vec2 position, glm::vec2 velocity) {
	setPosition(position);
	setVelocity(velocity);
}

void Pickup::update(float deltaTime) {
	if (!_active) {
		return;
	}
	move();
}

void Pickup::render() {

}

void Pickup::move() {
	_position += _velocity;
	if (_position.x < -500 || _position.x > 1300 ||
		_position.y < -500 || _position.y > 1300) {
		_active = false;
	}
}
