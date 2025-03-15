#pragma once
#include "Pickup.h"
#include "ScoreManager.h"
#include "AudioManager.h"
class Ring :
    public Pickup
{
private:
    int _scoreIncrease;
public:
    Ring(glm::vec2 position, glm::vec2 velocity);
    Ring(glm::vec2 position, glm::vec2 velocity, int scoreIncrease);
    void update();
    void render();
    void onPickup();
};