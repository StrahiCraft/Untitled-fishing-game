#pragma once
#include "Pickup.h"
#include "ScoreManager.h"
#include "AudioManager.h"
class Ring :
    public Pickup
{
public:
    Ring(glm::vec2 position, glm::vec2 velocity);
    void update(float deltaTime);
    void render();
    void onPickup();
};

