#include "Button.h"

Button::Button(glm::vec2 position, glm::vec2 scale, Sprite* background) {
	setPosition(position);
	setScale(scale);
	setSprite(background);
	_spriteBackground = true;
}

Button::Button(glm::vec2 position, glm::vec2 scale, string text, Sprite* fontSprite, Sprite* background) {
	setPosition(position);
	setScale(scale);
	setSprite(background);

	_textRenderer = new TextRenderer(position, 
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	_textRenderer->setText(text);

	_spriteBackground = true;
}

Button::Button(glm::vec2 position, glm::vec2 scale, string text, Sprite* fontSprite, glm::vec3 buttonColor) {
	setPosition(position);
	setScale(scale);
	_buttonColor = buttonColor;

	_textRenderer = new TextRenderer(glm::vec2(position.x - scale.x / 2 + 16 * (text.size() + 1), _position.y - 16),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	_textRenderer->setText(text);

	_spriteBackground = false;
}

void Button::onClick() {
	EventSystem::invokeChannel(_eventChannel);
}

void Button::setEvent(string eventChannel) {
	_eventChannel = eventChannel;
}

void Button::update(float deltaTime) {

}

void Button::render() {
	if (!_active) {
		return;
	}
	glPushMatrix();

	glTranslatef(_position.x, _position.y, 0.0f);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
	glScalef(_scale.x, _scale.y, 1.0f);

	if (_spriteBackground) {
		_sprite->render();
	}
	else {
		glBegin(GL_QUADS);
		glColor3f(_buttonColor.x, _buttonColor.y, _buttonColor.z);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(-0.5f, -0.5f);
		glEnd();
	}

	glPopMatrix();

	_textRenderer->render();
}
