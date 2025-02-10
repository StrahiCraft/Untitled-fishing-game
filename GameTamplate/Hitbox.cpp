#include "Hitbox.h"

Hitbox::Hitbox(glm::vec2 position, glm::vec2 size, Player* player) {
	setPosition(position);
	_hitboxSize = size;
	_playerReference = player;
}

void Hitbox::update() {
	if (!_active) {
		return;
	}

	glm::vec2 playerPos = _playerReference->getPosition();
	float minDistance = _hitboxSize.x + _hitboxSize.y;

	if (playerPos.x > _position.x - _hitboxSize.x / 2 && playerPos.x < _position.x + _hitboxSize.x / 2
		&& playerPos.y > _position.y - _hitboxSize.y / 2 && playerPos.y < _position.y + _hitboxSize.y / 2) {
		if (glm::distance(_playerReference->getPosition(),
			glm::vec2(_position.x - _hitboxSize.x / 2, _playerReference->getPosition().y)) <= minDistance) {
			minDistance = glm::distance(_playerReference->getPosition(), glm::vec2(_position.x - _hitboxSize.x / 2, _playerReference->getPosition().y));
			playerPos = glm::vec2(_position.x - _hitboxSize.x / 2, _playerReference->getPosition().y);
		}
		if (glm::distance(_playerReference->getPosition(),
			glm::vec2(_position.x + _hitboxSize.x / 2, _playerReference->getPosition().y)) <= minDistance) {
			minDistance = glm::distance(_playerReference->getPosition(), glm::vec2(_position.x + _hitboxSize.x / 2, _playerReference->getPosition().y));
			playerPos = glm::vec2(_position.x + _hitboxSize.x / 2, _playerReference->getPosition().y);
		}
		if (glm::distance(_playerReference->getPosition(),
			glm::vec2(_playerReference->getPosition().x, _position.y - _hitboxSize.y / 2)) <= minDistance) {
			minDistance = glm::distance(_playerReference->getPosition(), glm::vec2(_playerReference->getPosition().x, _position.y - _hitboxSize.y / 2));
			playerPos = glm::vec2(_playerReference->getPosition().x, _position.y - _hitboxSize.y / 2);
		}
		if (glm::distance(_playerReference->getPosition(),
			glm::vec2(_playerReference->getPosition().x, _position.y + _hitboxSize.y / 2)) <= minDistance) {
			minDistance = glm::distance(_playerReference->getPosition(), glm::vec2(_playerReference->getPosition().x, _position.y + _hitboxSize.y / 2));
			playerPos = glm::vec2(_playerReference->getPosition().x, _position.y + _hitboxSize.y / 2);
		}
		_playerReference->setPosition(playerPos);
	}
}

void Hitbox::render() {
	if (!_active) {
		return;
	}

	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0);
	glScalef(_hitboxSize.x, _hitboxSize.y, 0);

	glBegin(GL_LINE_LOOP);

	glColor3f(0, 1, 0);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);

	glEnd();

	glPopMatrix();
}
