#include "Fishing.h"

void Fishing::onStateEnter() {
	AudioManager::playSong("fishing");
	_progressBar = new ProgressBar(glm::vec2(400, 50), glm::vec2(500, 15),
		glm::vec3(1), glm::vec3(0.2f), glm::vec3(0.5f, 0, 0));
	_player->setActive(true);
	_player->setRotation(0);
	_player->setPosition(glm::vec2(400, 400));
	_player->setSpeedDebuff(0);
	_maxFishingTime = 30;
	_remainingFishingTime = _maxFishingTime;

	_ring = new Ring(glm::vec2(200), glm::vec2(0));
}

void Fishing::onStateUpdate(float deltaTime) {
	if (glm::distance(_player->getPosition(), _fish->getPosition()) <= _fish->getGoalCircleSize() + 16) {
		_fish->increaseCaptureScore(deltaTime);
	}
	else {	
		_remainingFishingTime -= deltaTime;
		_fish->increaseCaptureScore(-deltaTime);
	}

	_fish->update(deltaTime);
	_progressBar->updateProgressBar(_remainingFishingTime / _maxFishingTime);
	_progressBar->update(deltaTime);
	_player->update(deltaTime);
	_ring->update(deltaTime);

	if (glm::distance(_player->getPosition(), _ring->getPosition()) <= 35) {
		_ring->onPickup();
	}

	if (_remainingFishingTime < 0) {
		EventSystem::invokeChannel("GameOver");
	}
}

void Fishing::onStateExit() {}

void Fishing::render() {
	_fish->render();
	_player->render();
	_ring->render();
	_progressBar->render();
	ScoreManager::render();
}

float Fishing::getRemainigFishingTime() {
	return _remainingFishingTime;
}
