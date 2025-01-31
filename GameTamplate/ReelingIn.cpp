#include "ReelingIn.h"

ReelingIn::ReelingIn(Player* player, Fish* fish, glm::vec2 windowSize, float reelInThreshold, int bombCount) : GameState(player, fish)
{
	_windowSize = windowSize;
	_reelInThreshold = reelInThreshold;
	_reelInScore = _reelInThreshold / 2.0f;
	_bombCount = bombCount;
}

void ReelingIn::onStateEnter()
{
	_progressBar = new ProgressBar(glm::vec2(400, 50), glm::vec2(500, 15),
		glm::vec3(1), glm::vec3(0.2f), glm::vec3(0.5f, 0, 0));

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
}

void ReelingIn::checkForBombCollision() {
	for (Bomb* bomb : _bombs) {
		if (glm::distance(_player->getPosition(), bomb->getPosition()) <= 45) {
			_reelInScore -= 10;
			_progressBar->decayProgressBar(_reelInScore / _reelInThreshold);
			bomb->resetBomb();
		}
	}
}

void ReelingIn::handleScoreCalculation(float deltaTime) {
	if (_reelInScore < 0) {
		// TODO go to game over screen
		EventSystem::invokeChannel("StartFishing");
		cout << "GAME OVER" << endl;
		return;
	}

	_reelInScore += deltaTime;

	if (_reelInScore >= _reelInThreshold) {
		// TODO go to capture animation and then go back to fishing state
		EventSystem::invokeChannel("StartFishing");
		cout << "Fish caught!" << endl;
	}
}
