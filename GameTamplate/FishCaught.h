#pragma once
#include "GameState.h"
class FishCaught :
    public GameState
{
private:
    Sprite* _background;
    Button* _continueButton;

    TextRenderer* _fishName;
    TextRenderer* _fishWeight;
    TextRenderer* _score;
public:
    FishCaught(Player* player, Fish* fish, Sprite* fontSprite);
    void onStateEnter();
    void onStateUpdate();
    void onStateExit();
    void render();
};

