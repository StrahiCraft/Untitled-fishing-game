#pragma once
#include "Pickup.h"
#include "AudioManager.h"
class ChaosControl :
    public Pickup
{
private:
    float _timeStopTimer = 0;
    bool _timeStopped = false;
    Sprite* _chaosControlOverlay;
public:
    ChaosControl(glm::vec2 position, glm::vec2 velocity);
    void update();
    void render();
    void onPickup();
    ~ChaosControl();
};

