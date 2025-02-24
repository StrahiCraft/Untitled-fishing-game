#include "MainMenu.h"

MainMenu::MainMenu(Player* player, Fish* fish) : GameState(player, fish) {}

void MainMenu::onStateEnter() {
	_player->setActive(false);
	_fish->setActive(false);

	_title = new TextRenderer(glm::vec2(20, 680), new Sprite("Sprites/font.png", glm::vec2(64), 1, glm::vec2(15, 8), true), 54, 32);
	_title->setText("FISHING GAME");

	_buttons.push_back(new Button(glm::vec2(400, 550), glm::vec2(300, 70),
		"START", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0, 0.8f, 0)));
	_buttons.push_back(new Button(glm::vec2(400, 400), glm::vec2(300, 70),
		"BESTIARY", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0.7f, 0.3f, 0.2f)));
	_buttons.push_back(new Button(glm::vec2(400, 250), glm::vec2(300, 70),
		"SCORE", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0, 0.24f, 0.8f)));
	_buttons.push_back(new Button(glm::vec2(400, 100), glm::vec2(300, 70),
		"QUIT", new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), glm::vec3(0.8f, 0, 0)));
	_buttons[2]->setEvent("StartFishing");
	_buttons[3]->setEvent("StartFishing");
	_buttons[4]->setEvent("StartFishing");
	_buttons[5]->setEvent("Quit");
}

void MainMenu::onStateUpdate() {

}

void MainMenu::onStateExit() {
	_player->setActive(true);
	_fish->setActive(true);
}

void MainMenu::render() {
	_title->render();
	for (Button* button : _buttons) {
		button->render();
	}
}


