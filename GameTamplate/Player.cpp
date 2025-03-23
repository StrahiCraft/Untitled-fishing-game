#include "Player.h"

Player::Player(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, float acceleration) :
	GameObject(pos, vel, spr) {
	_speed = acceleration;
}

void Player::update() {
	handleInput();
	handleMovement();

	if (_velocity != glm::vec2(0)) {
		_rotation = getVelocityAngle();
	}

	checkEdges();
}

void Player::handleInput() {
	_newMovement = glm::vec2(0);

	if (Input::getKey('W')) {
		_newMovement.y += 1;
	}
	if (Input::getKey('S')) {
		_newMovement.y -= 1;
	}
	if (Input::getKey('A')) {
		_newMovement.x -= 1;
	}
	if (Input::getKey('D')) {
		_newMovement.x += 1;
	}
}

void Player::handleMovement() {
	if (_newMovement != _currentMovement) {
		_currentMovement = _newMovement;
		_velocityLerp = 0;
		_startVelocity = _velocity;
	}

	_velocity = (_startVelocity) * (1.0f - _velocityLerp) + (_currentMovement) * _velocityLerp;
	_velocityLerp += Time::getRealTime();

	if (_velocityLerp >= 1) {
		_velocityLerp = 1;
	}

	setPosition(getPosition() + _velocity * (_speed - _speedDebuff) * Time::getRealTime());
}

void Player::setSpeedDebuff(float fishWeight) {
	if (fishWeight * 5 > _speed) {
		_speedDebuff = 0.9f * _speed;
		return;
	}
	_speedDebuff = fishWeight * 5;
}

void Player::render() {
	if (!_active) {
		return;
	}

	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0.0f);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-28.0f, 0.0f, 0.0f);
	glScalef(_scale.x * 2, _scale.y * 2, 1.0f);

	getSprite()->render();

	glPopMatrix();

	glPushMatrix();
	
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(400, 800);
	glVertex2f(_position.x + 60 * -std::sin(_rotation / 57.2958f), _position.y + 60 * std::cos(_rotation / 57.2958f));
	glEnd();
}

void Player::renderBroken(float brokenTimer) {
	glPushMatrix();

	glTranslatef(_position.x, _position.y - brokenTimer * 50, 0.0f);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-28.0f, 0.0f, 0.0f);
	glScalef(_scale.x * 2, _scale.y * 2, 1.0f);

	getSprite()->render();

	glPopMatrix();

	glPushMatrix();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(400, 800);
	glVertex2f((400 + _position.x + 60 * -std::sin(_rotation / 57.2958f)) / 2.0f + brokenTimer * 15,
		(800 + _position.y - brokenTimer * 50 + 60 * std::cos(_rotation / 57.2958f)) / 2.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f((400 + _position.x + 60 * -std::sin(_rotation / 57.2958f)) / 2.0f - brokenTimer * 15,
		(800 + _position.y - brokenTimer * 50 + 60 * std::cos(_rotation / 57.2958f)) / 2.0f - brokenTimer * 30);
	glVertex2f(_position.x + 60 * -std::sin(_rotation / 57.2958f), _position.y - brokenTimer * 50 + 60 * std::cos(_rotation / 57.2958f));
	glEnd();
}

