#pragma once
#include "Pickup.h"
#include "AudioManager.h"
#include "EventSystem.h"

class BurstStream :
    public Pickup
{
private:
    bool _animationStarted = false;
    float _animationTimer = 0;
    Sprite* _burstStreamEffect;
public:
    BurstStream(glm::vec2 position, glm::vec2 velocity);
    void update();
    void render();
    void onPickup();
};

