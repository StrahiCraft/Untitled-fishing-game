#include "ScoreManager.h"

int ScoreManager::_score = 0;
TextRenderer* ScoreManager::_scoreText = new TextRenderer(glm::vec2(0, 750),
	new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);


void ScoreManager::init() {
	_score = 0;
	_scoreText = new TextRenderer(glm::vec2(0, 750),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);

	setScore(_score);
}

void ScoreManager::render() {
	_scoreText->render();
}

int ScoreManager::getScore() {
	return _score;
}

void ScoreManager::setScore(int newValue) {
	_score = newValue;
	_scoreText->setText("SCORE:" + to_string(_score));
}

void ScoreManager::increaseScore(int value) {
	_score += value;
	setScore(_score);
}
