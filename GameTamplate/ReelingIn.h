#pragma once
#include "GameState.h"
#include "Bomb.h"
#include "ProgressBar.h"
#include "BurstStream.h"
#include "Ring.h"

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
    Dictionary<glm::vec2, Sprite*> _stoneSprites;
    float _stoneSpriteOffset = 0;
    Pickup* _pickup;
public:
    ReelingIn(Player* player, Fish* fish, glm::vec2 windowSize, float reelInThreshold, int bombCount, Dictionary<glm::vec2, Sprite*> stoneSprites);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
    void clearBombs();
private:
    void checkForBombCollision();
    void handleScoreCalculation();
    void resetPickup();
};

