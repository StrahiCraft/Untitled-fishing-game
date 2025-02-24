#pragma once

#include "Player.h"
#include "Fish.h"
#include "Button.h"
#include "ScoreManager.h"
#include "AudioManager.h"

class GameState
{
protected:
	Player* _player;
	Fish* _fish;

	vector<Button*> _buttons;

	Button* _resumeButton;
	Button* _mainMenuButton;
	bool _paused = false;
public:
	GameState(Player* player, Fish* fish);
	~GameState();
	virtual void onStateEnter() = 0;
	virtual void onStateUpdate() = 0;
	virtual void onStateExit() = 0;
	virtual void render() = 0;

	void renderPauseMenu();
	void togglePause();

	void onClick(int x, int y);
};

