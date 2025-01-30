#include "Fishing.h"

void Fishing::onStateEnter() {

}

void Fishing::onStateUpdate(float deltaTime) {
	if (glm::distance(_player->getPosition(), _fish->getPosition()) <= _fish->getGoalCircleSize() + 16) {
		_fish->increaseCaptureScore(deltaTime * 2);
	}
	_fish->increaseCaptureScore(-deltaTime);

	_fish->update(deltaTime);
	_player->update(deltaTime);
}