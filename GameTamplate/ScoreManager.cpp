#include "ScoreManager.h"

int ScoreManager::_score = 0;
TextRenderer* ScoreManager::_scoreText = new TextRenderer(glm::vec2(0, 750),
	new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
vector<int> ScoreManager::_highScores;

void ScoreManager::init() {
	_score = 0;
	_scoreText = new TextRenderer(glm::vec2(0, 750),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);

	setScore(_score);

	ifstream file("HighScores.txt");

	string score;

	while (file >> score) {
		_highScores.push_back(stoi(score));
	}

	file.close();

	sortScores();
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

void ScoreManager::sortScores() {
	if (_highScores.size() < 2) {
		return;
	}

	bool swapped;

	for (int i = 0; i < _highScores.size() - 1; i++) {
		swapped = false;
		for (int j = 0; j < _highScores.size() - i - 1; j++) {
			if (_highScores[j] < _highScores[j + 1]) {
				swap(_highScores[j], _highScores[j + 1]);
				swapped = true;
			}
		}

		// If no two elements were swapped, then break
		if (!swapped)
			break;
	}
}

void ScoreManager::addNewScore(int score) {
	_highScores.push_back(score);

	sortScores();
	
	if (_highScores.size() > 5) {
		_highScores.pop_back();
	}

	ofstream file("HighScores.txt");

	for (int i = 0; i < _highScores.size(); i++) {
		file << _highScores[i] << endl;
	}

	file.close();
}

vector<int> ScoreManager::getHighScores() {
	return _highScores;
}
