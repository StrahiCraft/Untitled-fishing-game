#pragma once
#include "GameState.h"
class Intro :
    public GameState
{
private:
    TextRenderer* _introText;
    float _introLength = 3.6f;
    float _timer = 0;
public:
    Intro(Player* player, Fish* fish);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
};

