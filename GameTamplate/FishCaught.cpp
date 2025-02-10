#include "FishCaught.h"

FishCaught::FishCaught(Player* player, Fish* fish, Sprite* fontSprite) : GameState(player, fish) {
	_fishName = new TextRenderer(glm::vec2(400, 700),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	_fishWeight = new TextRenderer(glm::vec2(400, 600),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	_score = new TextRenderer(glm::vec2(400, 500),
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);

	_continueButton = new Button(glm::vec2(400, 230), glm::vec2(600, 300), "CONTINUE", fontSprite, glm::vec3(0, 0.8f, 0));
}

void FishCaught::onStateEnter() {
	AudioManager::stopMusic();
	AudioManager::playSound("fishCaught");

	_background = new Sprite("Sprites/fishCaughtMenu.png", glm::vec2(768), 1, glm::vec2(1), true);

	_continueButton->setEvent("StartFishing");

	_fishName->setText(_fish->getName());
	_fishWeight->setText("WEIGHT:" + to_string((int)_fish->getWeight()) + " KG");
	_score->setText("SCORE:" + to_string(ScoreManager::getScore()) + "->" +
		to_string(ScoreManager::getScore() + _fish->getScore()));
	ScoreManager::increaseScore(_fish->getScore());

	_player->setActive(false);
	_fish->setPosition(glm::vec2(225, 585));
	_fish->setScale(glm::vec2(3));
	_fish->setRotation(45);
	_fish->getSprite()->setSpriteFlip(glm::vec2(0));
	_buttons.push_back(*_continueButton);
}

void FishCaught::onStateUpdate() {

}

void FishCaught::onStateExit() {
	_fish->setScale(glm::vec2(1));
}

void FishCaught::render() {
	glPushMatrix();
	glTranslatef(16, 16, 0);
	_background->render();
	glPopMatrix();
	_fish->render();
	_continueButton->render();

	_fishName->render();
	_fishWeight->render();
	_score->render();
}
