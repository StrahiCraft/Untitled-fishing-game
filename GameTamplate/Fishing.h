#pragma once
#include "GameState.h"
class Fishing :
    public GameState
{
public:
    Fishing(Player* player, Fish* fish) : GameState(player, fish){}
    void onStateEnter();
    void onStateUpdate(float deltaTime);
    void onStateExit();
    void render();
};