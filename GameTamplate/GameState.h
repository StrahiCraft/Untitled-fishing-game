#pragma once

#include "Player.h"
#include "Fish.h"

class GameState
{
protected:
	Player* _player;
	Fish* _fish;

public:
	GameState(Player* player, Fish* fish);
	virtual void onStateEnter() = 0;
	virtual void onStateUpdate(float deltaTime) = 0;
};

