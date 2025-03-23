#pragma once
#include "GameState.h"
#include "Bomb.h"
#include "ProgressBar.h"
#include "BurstStream.h"
#include "BackgroundManager.h"
#include "Ring.h"

class ReelingIn :
    public GameState
{
private:
    float _reelInScore = 0;
    float _reelInThreshold;

    int _bombCount;
    vector<Bomb*> _bombs;

    glm::vec2 _windowSize;
    ProgressBar* _progressBar;

    Dictionary<glm::vec2, Sprite*> _stoneSprites;
    float _stoneSpriteOffset = 0;

    Pickup* _pickup;

    float _lineIntegrity;
    float _lineIntegrityDecaySpeed = 0.2f;
    bool _lineBroken = false;
    float _lineBrokenTimer = 0;
public:
    ReelingIn(Player* player, Fish* fish, glm::vec2 windowSize, float lineIntegrity, float lineStrength, int bombCount, Dictionary<glm::vec2, Sprite*> stoneSprites);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
    void clearBombs();
    float getLineStrength();
private:
    void checkForBombCollision();
    void resetPickup();
};