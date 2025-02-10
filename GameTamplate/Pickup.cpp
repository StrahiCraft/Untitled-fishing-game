#include "Pickup.h"

Pickup::Pickup(glm::vec2 position, glm::vec2 velocity) {
	setPosition(position);
	setVelocity(velocity);
}

void Pickup::update() {
	if (!_active) {
		return;
	}
	move();
}

void Pickup::render() {

}

float Pickup::getSize()
{
	return _sprite->getSize().x * _scale.x;
}

void Pickup::move() {
	_position += _velocity * Time::getDeltaTime();
	if (_position.x < -500 || _position.x > 1300 ||
		_position.y < -500 || _position.y > 1300) {
		_active = false;
	}
}
