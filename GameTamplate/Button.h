#pragma once
#include "GameObject.h"
#include "TextRenderer.h"
#include "EventSystem.h"

#include <freeglut.h>

class Button :
    public GameObject
{
private:
    TextRenderer* _textRenderer;
    glm::vec3 _buttonColor;
    string _eventChannel;

    bool _spriteBackground;
public:
    Button(glm::vec2 position, glm::vec2 scale, Sprite* background);
    Button(glm::vec2 position, glm::vec2 scale, string text, Sprite* fontSprite, Sprite* background);
    Button(glm::vec2 position, glm::vec2 scale, string text, Sprite* fontSprite, glm::vec3 buttonColor);

    void onClick();
    void setEvent(string eventChannel);
    void update(float deltaTime);
    void render();
};

