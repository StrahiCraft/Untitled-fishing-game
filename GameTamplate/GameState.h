#pragma once

#include "Player.h"
#include "Fish.h"
#include "Button.h"
#include "ScoreManager.h"

class GameState
{
protected:
	Player* _player;
	Fish* _fish;

	vector<Button> _buttons;
public:
	GameState(Player* player, Fish* fish);
	virtual void onStateEnter() = 0;
	virtual void onStateUpdate(float deltaTime) = 0;
	virtual void onStateExit() = 0;
	virtual void render() = 0;

	void onClick(int x, int y);
};

