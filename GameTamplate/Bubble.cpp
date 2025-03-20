#include "Bubble.h"

Bubble::Bubble() {
	std::string spriteFilePath = "Sprites/Bubbles/bubble_" + std::to_string(1 + rand() % 7);
	spriteFilePath += ".png";
	setSprite(new Sprite(spriteFilePath.c_str(), glm::vec2(16), 1, glm::vec2(1), true));
	resetBubble();
}

void Bubble::update() {
	setPosition(glm::vec2(_initialXPosition,
		_position.y + _riseSpeed * Time::getDeltaTime()));

	if (_position.y > 1000) {
		resetBubble();
	}
}

void Bubble::render() {
	glPushMatrix();
	glTranslatef(_position.x, _position.y, 0);
	glScalef(_scale.x, _scale.y, 1);

	_sprite->render();

	glPopMatrix();
}

void Bubble::resetBubble() {
	_position = glm::vec2(rand() % 800, -100 - rand() % 800);
	_initialXPosition = _position.x;
	_shimmyDistance = (rand() % 200) + 100;
	_shimmySpeed = (rand() % 10) - 5;
	_riseSpeed = rand() % 100 + 30;
	_scale = glm::vec2(rand() % 2 + 1);
}
