#include "ReelingIn.h"

ReelingIn::ReelingIn(Player* player, Fish* fish, glm::vec2 windowSize, float reelInScore, int bombCount) : GameState(player, fish)
{
	_windowSize = windowSize;
	_reelInThreshold = 60;
	_reelInScore = reelInScore;
	_bombCount = bombCount;
	_player->setSpeedDebuff(fish->getWeight());
}

void ReelingIn::onStateEnter()
{
	AudioManager::playSong("reelingIn");

	_progressBar = new ProgressBar(glm::vec2(400, 50), glm::vec2(500, 15),
		glm::vec3(1), glm::vec3(0.2f), glm::vec3(1));
	_progressBar->updateProgressBar((_reelInScore * 2) / _reelInThreshold);
	_progressBar->decayProgressBar(_reelInScore / _reelInThreshold);

	for (int i = 0; i < _bombCount; i++) {
		_bombs.push_back(new Bomb(glm::vec2(0), glm::vec2(0, -150),
			new Sprite("Sprites/bomb.png", glm::vec2(32), 1, glm::vec2(1), true), _windowSize));
		_bombs[i]->resetBomb();
		_bombs[i]->setScale(glm::vec2(2));
	}
}

void ReelingIn::onStateUpdate(float deltaTime)
{
	_progressBar->updateProgressBar(_reelInScore / _reelInThreshold);
	checkForBombCollision();

	_player->update(deltaTime);
	_progressBar->update(deltaTime);
	_fish->setPosition(_player->getPosition());
	_fish->setRotation(_player->getRotation() + 90);

	for (int i = 0; i < _bombCount; i++) {
		_bombs[i]->update(deltaTime);
	}

	handleScoreCalculation(deltaTime);
}

void ReelingIn::render()
{
	_player->render();
	_fish->render();

	for (int i = 0; i < _bombCount; i++) {
		_bombs[i]->render();
	}
	_progressBar->render();
	ScoreManager::render();
}

void ReelingIn::onStateExit(){}

void ReelingIn::checkForBombCollision() {
	for (Bomb* bomb : _bombs) {
		if (glm::distance(_player->getPosition(), bomb->getPosition()) <= 45) {
			AudioManager::playSound("explode");
			_reelInScore -= 10;
			_progressBar->changeDecayColor(glm::vec3(0.5f, 0, 0));
			_progressBar->decayProgressBar(_reelInScore / _reelInThreshold);
			bomb->resetBomb();
		}
	}
}

void ReelingIn::handleScoreCalculation(float deltaTime) {
	if (_reelInScore < 0) {
		// TODO go to game over screen
		EventSystem::invokeChannel("GameOver");
		cout << "GAME OVER" << endl;
		return;
	}

	_reelInScore += deltaTime;

	if (_reelInScore >= _reelInThreshold) {
		EventSystem::invokeChannel("FishCaught");
		cout << "Fish caught!" << endl;
	}
}
