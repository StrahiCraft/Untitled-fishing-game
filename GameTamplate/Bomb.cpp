#include "Bomb.h"


Bomb::Bomb()
{
}

Bomb::Bomb(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, glm::vec2 windowSize) : GameObject(pos, vel, spr)
{
	_windowSize = windowSize;
}

void Bomb::update()
{
	if (!_active) {
		return;
	}

	setPosition(getPosition() + _velocity * Time::getDeltaTime());

	if (getPosition().y < -100) {
		resetBomb();
	}
}

void Bomb::render()
{
	if (!_active) {
		return;
	}

	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0.0f);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glScalef(_scale.x, _scale.y, 1.0f);
	glTranslatef(-_sprite->getSize().x / 2, -_sprite->getSize().y / 2, 0.0f);

	getSprite()->render();

	glPopMatrix();
}

void Bomb::resetBomb()
{
	setPosition(glm::vec2(rand() % (int)_windowSize.x, _windowSize.y + 100 + rand() % 800));
}
