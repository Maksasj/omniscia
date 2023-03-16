#include "controls.h"

std::unordered_map<omniscia::core::PlayerController, bool> omniscia::core::Controls::controlStates = {
    {omniscia::core::PlayerController::JUMP,        false},
    {omniscia::core::PlayerController::DOWN,        false},
    {omniscia::core::PlayerController::LEFT,        false},
    {omniscia::core::PlayerController::RIGHT,       false},
    {omniscia::core::PlayerController::TIME_JUMP,   false},
};

std::unordered_map<u8, std::pair<omniscia::core::PlayerController, omniscia::core::ActionType>> omniscia::core::Controls::keyBindigs = {
    {'W', {omniscia::core::PlayerController::JUMP,       ActionType::PRESS  }},
    {'S', {omniscia::core::PlayerController::DOWN,       ActionType::PRESS  }},
    {'A', {omniscia::core::PlayerController::LEFT,       ActionType::PRESS  }},
    {'D', {omniscia::core::PlayerController::RIGHT,      ActionType::PRESS  }},
    {'T', {omniscia::core::PlayerController::TIME_JUMP,  ActionType::RELEASE}}
};

bool omniscia::core::Controls::get(const PlayerController& action) {
    return controlStates[action];
}

void omniscia::core::Controls::handle_input(GLFWwindow *window) {
    for(auto &key : keyBindigs) {
        auto actionType = key.second.second;

        if (glfwGetKey(window, key.first) == actionType) {
            controlStates[key.second.first] = true;
        } else {
            controlStates[key.second.first] = false;
        }
    }
}
