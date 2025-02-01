#pragma once
#include "GameObject.h"
#include "EventSystem.h"
#include "FishStats.h"

class Fish :
    public GameObject
{
private:
    primitive _goalCircle;
    primitive _currentFishingCircle;
    glm::vec2 _windowSize;
    glm::vec2 _destination;

    FishStats* _fishStats;
    float _currentCircleSize;

    bool _reelingIn = false;
public:
    Fish(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, glm::vec2 windowSize);

    float getGoalCircleSize();
    int getScore();
    float getWeight();

    void update(float deltaTime);
    void render();

    void increaseCaptureScore(float dt);
    void resetFish(string statsFilePath);
private:
    void randomizePosition();
    void randomizeDestination();
};

