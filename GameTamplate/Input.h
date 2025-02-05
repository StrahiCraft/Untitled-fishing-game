#pragma once
#include "EventSystem.h"

#include <stdlib.h>
#include <freeglut.h>
#include <glm.hpp>
#include <iostream>

class Input {
public:
    static bool _isCursorLocked;

private:
    static bool _keyStates[256];
    static bool _keyDownDected[256];

    static glm::vec3 _mousePosition;

    static glm::vec3 _lastPosition;
    static glm::vec3 _deltaPosition;

public:
    static void mouseMove(int x, int y);
    static void setCallbackFunctions();
    static bool getKeyDown(int keycode);
    static bool getKey(int keycode);
    static bool getKeyUp(int keycode);
    static void keyboard(unsigned char key, int x, int y);
    static void keyboardUp(unsigned char key, int x, int y);
    static void mouseClick(int button, int state, int x, int y);
    static bool isAnyKeyPressed();
    static void update();
    static void updateCursorLock();
    static glm::vec3 getMouse();
};
