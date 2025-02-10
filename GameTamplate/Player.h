#pragma once
#include "GameObject.h"
#include "Input.h"
class Player :
    public GameObject
{
private:
    glm::vec2 _newMovement = glm::vec2(0);
    glm::vec2 _currentMovement = glm::vec2(0);

    float _speed;
    float _speedDebuff;

    float _velocityLerp = 0;
    glm::vec2 _startVelocity = glm::vec2(0);
public:
    Player(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, float speed);

    virtual void update();
    virtual void render();

    void handleInput();
    void handleMovement();

    float getSpeed() { return _speed; }
    void setSpeedDebuff(float fishWeight);
};

