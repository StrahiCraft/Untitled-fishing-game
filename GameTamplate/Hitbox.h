#pragma once
#include "Player.h"
class Hitbox :
    public GameObject
{
private:
    glm::vec2 _hitboxSize;
    Player* _playerReference;
public:
    Hitbox(glm::vec2 position, glm::vec2 size, Player* player);
    void update();
    void render();
};

