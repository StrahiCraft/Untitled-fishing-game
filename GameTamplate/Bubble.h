#pragma once
#include "GameObject.h"
#include <string>

class Bubble :
    public GameObject
{
private:
    float _riseSpeed;
    float _shimmySpeed;
    float _shimmyDistance;
    float _initialXPosition;
public:
    Bubble();

    void update();
    void render();
private:
    void resetBubble();
};

