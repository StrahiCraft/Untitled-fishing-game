#pragma once
#include "GameObject.h"
#include "Input.h"
class Player :
    public GameObject
{
private:
    glm::vec2 _movement = glm::vec2(0);

    float _acceleration;
    float _speedCap;

    float _velocityLerp = 0;
    glm::vec2 _startVelocity = glm::vec2(0);
public:
    Player(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, float acceleration, float speedCap);

    virtual void update(float deltaTime);
    virtual void render();

    void handleInput();
    void handleMovement(float deltaTime);

    float getAcceleration() { return _acceleration; }
};

