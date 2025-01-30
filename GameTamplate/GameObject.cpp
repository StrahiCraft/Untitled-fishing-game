#include "GameObject.h"

float GameObject::getVelocityAngle() {
	return -std::acos(_velocity.y
		/ (std::sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y))) * 57.2958f * glm::normalize(_velocity).x;
}