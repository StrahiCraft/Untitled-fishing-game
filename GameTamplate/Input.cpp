#include "Input.h"


bool Input::_keyStates[256] = { false };
bool Input::_keyDownDected[256] = { false };
bool Input::_isCursorLocked = false;

glm::vec3 Input::_mousePosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Input::_lastPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Input::_deltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);

void Input::mouseMove(int x, int y)
{
    _mousePosition.x = x;
    _mousePosition.y = y;
}

void Input::setCallbackFunctions() {
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
}

bool Input::getKeyDown(int keycode) {
    if (_keyStates[keycode] && !_keyDownDected[keycode]) {
        _keyDownDected[keycode] = true;
        return true;
    }
    return false;
}

bool Input::getKey(int keycode) {
    return _keyStates[keycode];
}

bool Input::getKeyUp(int keycode) {
    if (!_keyStates[keycode] && _keyDownDected[keycode])
        return true;

    return false;
}

void Input::keyboard(unsigned char key, int x, int y) {
    if (isalpha(key))
        key = toupper(key);

    _keyStates[key] = true;
}

void Input::keyboardUp(unsigned char key, int x, int y) {
    if (isalpha(key))
        key = toupper(key);

    _keyStates[key] = false;
    _keyDownDected[key] = false;
}

void Input::mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "Cursor Position: x = " << x << ", y = " << y << std::endl;
    }
}

bool Input::isAnyKeyPressed() {
    for (int i = 0; i < 256; ++i) {
        if (_keyStates[i]) {
            return true;
        }
    }
    return false;
}

void Input::update() {
    updateCursorLock();

    if (!_isCursorLocked) {
        _deltaPosition = _lastPosition - _mousePosition;
        _lastPosition = _mousePosition;
    }
    else {
        _deltaPosition.x = glutGet(GLUT_WINDOW_WIDTH) / 2 - _mousePosition.x;
        _deltaPosition.y = glutGet(GLUT_WINDOW_HEIGHT) / 2 - _mousePosition.y;
    }

    for (int i = 0; i < 256; i++) {
        if (!_keyStates[i]) {
            _keyDownDected[i] = false;
        }
    }
}

void Input::updateCursorLock() {
    if (_isCursorLocked) {
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    }
    else {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

glm::vec3& Input::getMouse() { return _deltaPosition; }