#pragma once
#include "GameObject.h"
class Pickup :
    public GameObject
{
public:
    Pickup(glm::vec2 position, glm::vec2(velocity));
    void update(float deltaTime);
    void render();
    virtual void onPickup() = 0;
protected:
    void move();
};

