#include "Intro.h"

Intro::Intro(Player* player, Fish* fish) : GameState(player, fish) {

}

void Intro::onStateEnter() {
	_introText = new TextRenderer(glm::vec2(30, 700),
		new Sprite("Sprites/font.png", glm::vec2(64), 1, glm::vec2(15, 8), true), 54, 32);
	_introText->setText("FISHING GAME_____BY__STRAHINJA_NIKOLIC_6029");
}

void Intro::onStateUpdate() {
	_timer += Time::getRealTime();
	if (_timer > _introLength) {
		EventSystem::invokeChannel("MainMenu");
	}
}

void Intro::onStateExit() {

}

void Intro::render() {
	_introText->render();
}
