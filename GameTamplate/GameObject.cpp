#include "GameObject.h"

float GameObject::getVelocityAngle() {
	return atan2(-_velocity.x, _velocity.y) * 57.295827908797774375395898255342f;
}