#include "GameOver.h"

GameOver::GameOver(Player* player, Fish* fish) : GameState(player, fish) {

}

void GameOver::onStateEnter() {
	_gameOverText = new TextRenderer(glm::vec2(250, 700),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	_gameOverText->setText("GAME OVER");

	_scoreText = new TextRenderer(glm::vec2(0, 600),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	_scoreText->setText("SCORE: " + std::to_string(ScoreManager::getScore()));

	ScoreManager::addNewScore(ScoreManager::getScore());

	_resumeButton = new Button(glm::vec2(400, 450), glm::vec2(300, 70),
		"TRY AGAIN", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0, 0.8f, 0));
	_resumeButton->setEvent("Reset");

	_quitButton = new Button(glm::vec2(400, 250), glm::vec2(300, 70),
		"QUIT", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0.8f, 0, 0));
	_quitButton->setEvent("MainMenu");

	_buttons.push_back(_resumeButton);
	_buttons.push_back(_quitButton);
}

void GameOver::onStateUpdate() {

}

void GameOver::onStateExit() {

}

void GameOver::render() {
	_gameOverText->render();
	_scoreText->render();

	_resumeButton->render();
	_quitButton->render();
}
