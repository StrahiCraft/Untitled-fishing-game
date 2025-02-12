#include "GameState.h"

GameState::GameState(Player* player, Fish* fish) {
	_player = player;
	_fish = fish;
}

void GameState::onClick(int x, int y) {
	cout << "Clicked at: " << x << ", " << y << endl;
	for (int i = 0; i < _buttons.size(); i++) {
		cout << "Button hitbox from: " << _buttons[i]->getPosition().x - _buttons[i]->getScale().x / 2
			<< ", " << _buttons[i]->getPosition().y - _buttons[i]->getScale().y / 2 <<
			", to: " << _buttons[i]->getPosition().x + _buttons[i]->getScale().x / 2
			<< ", " << _buttons[i]->getPosition().y + _buttons[i]->getScale().y / 2 << endl;
		if (x > _buttons[i]->getPosition().x - _buttons[i]->getScale().x / 2
			&& x < _buttons[i]->getPosition().x + _buttons[i]->getScale().x / 2
			&& y > _buttons[i]->getPosition().y - _buttons[i]->getScale().y / 2
			&& y < _buttons[i]->getPosition().y + _buttons[i]->getScale().y / 2) {
			_buttons[i]->onClick();
		}
	}
}
