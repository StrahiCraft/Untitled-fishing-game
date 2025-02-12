#pragma once
#include "GameState.h"
class MainMenu :
    public GameState
{
private:
    TextRenderer* _title;
public:
    MainMenu(Player* player, Fish* fish);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
};

