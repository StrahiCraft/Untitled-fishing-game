#pragma once
#include "GameObject.h"
#include "EventSystem.h"

class Fish :
    public GameObject
{
private:
    primitive _goalCircle;
    primitive _currentFishingCircle;
    glm::vec2 _windowSize;
    glm::vec2 _destination;

    float _fishSpeed;
    float _captureRate;
    float _currentCircleSize;
    float _goalCircleSize;

    bool _reelingIn = false;
public:
    Fish(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, glm::vec2 windowSize);

    float getGoalCircleSize();

    void update(float deltaTime);
    void render();

    void increaseCaptureScore(float dt);
    void resetFish();

private:
    void randomizePosition();
    void randomizeDestination();
};

