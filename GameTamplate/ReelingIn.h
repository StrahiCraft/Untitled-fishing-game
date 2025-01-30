#pragma once
#include "GameState.h"
class ReelingIn :
    public GameState
{
public:
    ReelingIn(Player* player, Fish* fish) : GameState(player, fish) {}
    void onStateEnter();
    void onStateUpdate(float deltaTime);
};

