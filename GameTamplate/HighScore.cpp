
#include "HighScore.h"

HighScore::HighScore(Player* player, Fish* fish) : GameState(player, fish) {
	_title = new TextRenderer(glm::vec2(30, 700),
		new Sprite("Sprites/font.png", glm::vec2(64), 1, glm::vec2(15, 8), true), 54, 32);
	_title->setText("HIGH SCORES");

	_backButton = new Button(glm::vec2(400, 100), glm::vec2(300, 70),
		"BACK", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0.8f, 0, 0));
	_backButton->setEvent("MainMenu");
	_buttons.push_back(_backButton);

	_highScoreText = new TextRenderer(glm::vec2(30, 600),
		new Sprite("Sprites/font.png", glm::vec2(64), 1, glm::vec2(15, 8), true), 54, 32);
}

void HighScore::onStateEnter() {
	string highScoreText = "";
	vector<int> highScores = ScoreManager::getHighScores();

	if (highScores.size() == 0) {
		_highScoreText->setText("NO SCORES YET");
		return;
	}

	for (int i = 0; i < highScores.size(); i++) {
		highScoreText.append(to_string(i + 1) + ". " + to_string(highScores[i]) + "_");
	}

	_highScoreText->setText(highScoreText);
}

void HighScore::onStateUpdate() {

}

void HighScore::onStateExit() {

}

void HighScore::render() {
	_title->render();
	_highScoreText->render();
	_backButton->render();
}
