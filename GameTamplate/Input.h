#pragma once
#include <stdlib.h>
#include <freeglut.h>
#include <glm.hpp>
#include <iostream>

class Input {
public:
    static bool is_cursor_locked;

private:
    static bool key_states[256];
    static bool key_down_dected[256];

    static glm::vec3 mouse_position;

    static glm::vec3 last_position;
    static glm::vec3 delta_position;

public:
    static void mouse_move(int x, int y);
    static void set_callback_functions();
    static bool get_key_down(int keycode);
    static bool get_key(int keycode);
    static bool get_key_up(int keycode);
    static void keyboard(unsigned char key, int x, int y);
    static void keyboard_up(unsigned char key, int x, int y);
    static void mouse_click(int button, int state, int x, int y);
    static bool is_any_key_pressed();
    static void update();
    static void update_cursor_lock();
    static glm::vec3& get_mouse();
};

bool Input::key_states[256] = { false };
bool Input::key_down_dected[256] = { false };
bool Input::is_cursor_locked = false;

glm::vec3 Input::mouse_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Input::last_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Input::delta_position = glm::vec3(0.0f, 0.0f, 0.0f);

void Input::mouse_move(int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void Input::set_callback_functions() {
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(mouse_click);
}

bool Input::get_key_down(int keycode) {
    if (key_states[keycode] && !key_down_dected[keycode]) {
        key_down_dected[keycode] = true;
        return true;
    }
    return false;
}

bool Input::get_key(int keycode) {
    return key_states[keycode];
}

bool Input::get_key_up(int keycode) {
    if (!key_states[keycode] && key_down_dected[keycode])
        return true;

    return false;
}

void Input::keyboard(unsigned char key, int x, int y) {
    if (isalpha(key))
        key = toupper(key);

    key_states[key] = true;
}

void Input::keyboard_up(unsigned char key, int x, int y) {
    if (isalpha(key))
        key = toupper(key);

    key_states[key] = false;
    key_down_dected[key] = false;
}

void Input::mouse_click(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "Cursor Position: x = " << x << ", y = " << y << std::endl;
    }
}

bool Input::is_any_key_pressed() {
    for (int i = 0; i < 256; ++i) {
        if (key_states[i]) {
            return true;
        }
    }
    return false;
}

void Input::update() {
    update_cursor_lock();

    if (!is_cursor_locked) {
        delta_position = last_position - mouse_position;
        last_position = mouse_position;
    }
    else {
        delta_position.x = glutGet(GLUT_WINDOW_WIDTH) / 2 - mouse_position.x;
        delta_position.y = glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouse_position.y;
    }

    for (int i = 0; i < 256; i++) {
        if (!key_states[i]) {
            key_down_dected[i] = false;
        }
    }
}

void Input::update_cursor_lock() {
    if (is_cursor_locked) {
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    }
    else {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

glm::vec3& Input::get_mouse() { return delta_position; }
