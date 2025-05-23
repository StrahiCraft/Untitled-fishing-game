#pragma once
#include "GameObject.h"
class ProgressBar :
    public GameObject
{
private:
    glm::vec3 _progressBarColor;
    glm::vec3 _backgroundColor;
    glm::vec3 _fastDecayColor;
    float _progress;
    float _maxProgress = 1;
    float _fastDecayStart;
    float _fastDecayProgress;
    float _fastDecayGoal;
    float _fastDecayTimer;
public:
    ProgressBar();
    ProgressBar(glm::vec2 position, glm::vec2 scale,
        glm::vec3 progressBarColor, glm::vec3 backgroundColor, glm::vec3 fastDecayColor);
    void update();
    void updateProgressBar(float newProgress);
    void render();
    void drawProgressLayer(float multiplier, glm::vec3 color);
    void decayProgressBar(float newProgress);
    float getProgress();
    void setProgress(float progress);
    void changeDecayColor(glm::vec3 newColor);
    void changeColor(glm::vec3 newColor);
    void setMaxProgress(float value);
    float getMaxProgress();
};
