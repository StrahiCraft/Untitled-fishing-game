#pragma once
#include "GameObject.h"
class Bomb :
    public GameObject
{
private:
    glm::vec2 _windowSize;
public:
    Bomb();
    Bomb(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr, glm::vec2 windowSize);

    void update(float deltaTime);
    void render();
    void resetBomb();
};

