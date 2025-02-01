#include "Fishing.h"

void Fishing::onStateEnter() {
	_player->setPosition(glm::vec2(400, 400));
	_player->setSpeedDebuff(0);
}

void Fishing::onStateUpdate(float deltaTime) {
	if (glm::distance(_player->getPosition(), _fish->getPosition()) <= _fish->getGoalCircleSize() + 16) {
		_fish->increaseCaptureScore(deltaTime * 2);
	}
	_fish->increaseCaptureScore(-deltaTime);

	_fish->update(deltaTime);
	_player->update(deltaTime);
}

void Fishing::render() {
	_fish->render();
	_player->render();
}
