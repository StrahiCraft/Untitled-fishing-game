#pragma once
#include "GameState.h"
#include "ProgressBar.h"
#include "Ring.h"
#include "ChaosControl.h"
#include "Hitbox.h"
#include "BackgroundManager.h"
class Fishing :
    public GameState
{
private:
    ProgressBar* _progressBar;
    float _maxFishingTime;
    float _remainingFishingTime;
    Pickup* _pickup;
    Dictionary<glm::vec2, Hitbox*> _stoneHitboxes;
    Dictionary<glm::vec2, Sprite*> _stoneSprites;
public:
    Fishing(Player* player, Fish* fish, float lineIntegrity);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
    float getRemainigFishingTime();
    float getLineStrength();
    Dictionary<glm::vec2, Sprite*> getStoneSprites();
private:
    void resetPickup();
};