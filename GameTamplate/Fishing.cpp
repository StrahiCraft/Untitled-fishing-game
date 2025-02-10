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

	_hitbox = new Hitbox(glm::vec2(200), glm::vec2(64), _player);

	resetPickup();
}

void Fishing::onStateUpdate() {

	if (!_pickup->getActive()) {
		resetPickup();
	}

	if (glm::distance(_player->getPosition(), _fish->getPosition()) <= _fish->getGoalCircleSize() + 16) {
		_fish->increaseCaptureScore(1);
	}
	else {	
		_remainingFishingTime -= Time::getDeltaTime();
		_fish->increaseCaptureScore(-1);
	}

	_fish->update();
	_progressBar->updateProgressBar(_remainingFishingTime / _maxFishingTime);
	_progressBar->update();
	_hitbox->update();
	_player->update();
	_pickup->update();

	if (glm::distance(_player->getPosition(), _pickup->getPosition()) <= _pickup->getSize()) {
		_pickup->onPickup();
	}

	if (_remainingFishingTime < 0) {
		EventSystem::invokeChannel("GameOver");
	}
}

void Fishing::onStateExit() {}

void Fishing::render() {
	_fish->render();
	_player->render();
	_pickup->render();
	_hitbox->render();
	_progressBar->render();
	ScoreManager::render();
}

float Fishing::getRemainigFishingTime() {
	return _remainingFishingTime;
}

void Fishing::resetPickup() {
	// change to the number of pickups implemented
	int pickupTypeCount = 2;

	switch (rand() % pickupTypeCount) {
	case 0:
		_pickup = new Ring(glm::vec2(-499 + rand() % 500, 50 + rand() % 700), glm::vec2(50 + rand() % 200, -1 + rand() % 2));
		break;
	case 1:
		_pickup = new ChaosControl(glm::vec2(-499 + rand() % 500, 50 + rand() % 700), glm::vec2(50 + rand() % 200, -1 + rand() % 2));
		break;
	default:
		_pickup = new Ring(glm::vec2(-499 + rand() % 500, 50 + rand() % 700), glm::vec2(50 + rand() % 200, -1 + rand() % 2));
		break;
	}
}
