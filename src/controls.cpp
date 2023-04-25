#include "controls.h"

omniscia::core::Controls::Controls() {
    controlStates = {
        {omniscia::core::PlayerController::JUMP,        false},
        {omniscia::core::PlayerController::DOWN,        false},
        {omniscia::core::PlayerController::LEFT,        false},
        {omniscia::core::PlayerController::RIGHT,       false},
        {omniscia::core::PlayerController::TIME_JUMP,   false},
    };

    keyBindigs = {
        {'W', {omniscia::core::PlayerController::JUMP,       ActionType::PRESS  }},
        {'S', {omniscia::core::PlayerController::DOWN,       ActionType::PRESS  }},
        {'A', {omniscia::core::PlayerController::LEFT,       ActionType::PRESS  }},
        {'D', {omniscia::core::PlayerController::RIGHT,      ActionType::PRESS  }},
        {'T', {omniscia::core::PlayerController::TIME_JUMP,  ActionType::RELEASE}},
    };

    mouseBindigs = {
        {GLFW_MOUSE_BUTTON_RIGHT, {omniscia::core::MouseController::RIGHT_CLICK, ActionType::PRESS  }},
        {GLFW_MOUSE_BUTTON_LEFT, {omniscia::core::MouseController::LEFT_CLICK, ActionType::PRESS  }},
    };
}

omniscia::core::Vec2f omniscia::core::Controls::get_mouse() {
    return _mousePos;
}

bool omniscia::core::Controls::get(const PlayerController& action) {
    return controlStates[action];
}

bool omniscia::core::Controls::get(const MouseController& action) {
    return controlStates[action];
}

void omniscia::core::Controls::handle_input(GLFWwindow *window) {
    for(auto &key : keyBindigs) {
        auto& actionType = key.second.second;

        if (glfwGetKey(window, key.first) == actionType) {
            controlStates[key.second.first] = true;
        } else {
            controlStates[key.second.first] = false;
        }
    }

    for(auto &key : mouseBindigs) {
        auto& actionType = key.second.second;

        if (glfwGetMouseButton(window, key.first) == actionType) {
            controlStates[key.second.first] = true;
        } else {
            controlStates[key.second.first] = false;
        }
    }

    f64 xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    _mousePos.x = 2.0f * (xpos / Properties::screenWidth) - 1.0f;
    _mousePos.y = 2.0f * (ypos / Properties::screenHeight) - 1.0f;
    _mousePos.x *= Properties::screenWidth / (f32)Properties::screenHeight;
    _mousePos.y = -_mousePos.y;
}
