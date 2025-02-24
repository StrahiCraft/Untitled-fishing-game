#pragma once
#include "GameState.h"
class GameOver :
    public GameState
{
private:
    TextRenderer* _gameOverText;
    TextRenderer* _scoreText;
    Button* _retryButton;
    Button* _quitButton;
public:
    GameOver(Player* player, Fish* fish);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
};

