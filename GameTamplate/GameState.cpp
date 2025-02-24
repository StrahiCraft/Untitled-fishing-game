#include "GameState.h"

GameState::GameState(Player* player, Fish* fish) {
	_player = player;
	_fish = fish;

	_resumeButton = new Button(glm::vec2(400, 600), glm::vec2(250, 100), "RESUME",
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0, 1, 0));

	_mainMenuButton = new Button(glm::vec2(400, 400), glm::vec2(400, 100), "MAIN MENU",
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(1, 0, 0));

	_resumeButton->setEvent("Pause");
	_mainMenuButton->setEvent("MainMenu");

	_resumeButton->setActive(false);
	_mainMenuButton->setActive(false);

	_buttons.push_back(_resumeButton);
	_buttons.push_back(_mainMenuButton);
}

GameState::~GameState() {
	delete this;
}

void GameState::renderPauseMenu() {
	glDisable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glVertex2f(0, 0);
	glVertex2f(800, 0);
	glVertex2f(800, 800);
	glVertex2f(0, 800);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	_resumeButton->render();
	_mainMenuButton->render();
}

void GameState::togglePause() {
	_paused = !_paused;

	_resumeButton->setActive(_paused);
	_mainMenuButton->setActive(_paused);
}

void GameState::onClick(int x, int y) {
	for (int i = 0; i < _buttons.size(); i++) {
		if (x > _buttons[i]->getPosition().x - _buttons[i]->getScale().x / 2
			&& x < _buttons[i]->getPosition().x + _buttons[i]->getScale().x / 2
			&& y > _buttons[i]->getPosition().y - _buttons[i]->getScale().y / 2
			&& y < _buttons[i]->getPosition().y + _buttons[i]->getScale().y / 2) {
			_buttons[i]->onClick();
		}
	}
}
