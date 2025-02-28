#pragma once
#include "GameState.h"
class HighScore : public GameState
{
private:
	TextRenderer* _title;
	TextRenderer* _highScoreText;
	Button* _backButton;
public:
	HighScore(Player* player, Fish* fish);
	void onStateEnter();
	void onStateUpdate();
	void onStateExit();
	void render();
};