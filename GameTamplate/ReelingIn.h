#pragma once
#include "GameState.h"
#include "Bomb.h"
#include "ProgressBar.h"
class ReelingIn :
    public GameState
{
private:
    float _reelInScore;
    float _reelInThreshold;
    int _bombCount;
    vector<Bomb*> _bombs;
    glm::vec2 _windowSize;
    ProgressBar* _progressBar;
public:
    ReelingIn(Player* player, Fish* fish, glm::vec2 windowSize, float reelInThreshold, int bombCount);
    void onStateEnter();
    void onStateUpdate(float deltaTime);
    void onStateExit();
    void render();
private:
    void checkForBombCollision();
    void handleScoreCalculation(float deltaTime);
};

