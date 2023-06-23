#include "controls.h"

omniscia::core::Controls::Controls() {
    controlStates = {
        {omniscia::core::PlayerController::JUMP,            false},
        {omniscia::core::PlayerController::DOWN,            false},
        {omniscia::core::PlayerController::LEFT,            false},
        {omniscia::core::PlayerController::RIGHT,           false},
        {omniscia::core::PlayerController::TIME_JUMP,       false},
        {omniscia::core::PlayerController::PAUSE,           false},
        {omniscia::core::PlayerController::DEBUGUI,         false}, 
    };

    keyBindigs = {
        {'W',               {omniscia::core::PlayerController::JUMP,       ActionType::PRESS    }},
        {'S',               {omniscia::core::PlayerController::DOWN,       ActionType::PRESS    }},
        {'A',               {omniscia::core::PlayerController::LEFT,       ActionType::PRESS    }},
        {'D',               {omniscia::core::PlayerController::RIGHT,      ActionType::PRESS    }},
        {'T',               {omniscia::core::PlayerController::TIME_JUMP,  ActionType::RELEASE  }},
        {'E',               {omniscia::core::PlayerController::INTERACT,   ActionType::PRESS    }},
        {GLFW_KEY_ESCAPE,   {omniscia::core::PlayerController::PAUSE,      ActionType::PRESS    }},
        {GLFW_KEY_F3,       {omniscia::core::PlayerController::DEBUGUI,    ActionType::PRESS    }},
    };

    mouseBindigs = {
        {GLFW_MOUSE_BUTTON_RIGHT, {omniscia::core::MouseController::RIGHT_CLICK, ActionType::PRESS  }},
        {GLFW_MOUSE_BUTTON_LEFT, {omniscia::core::MouseController::LEFT_CLICK, ActionType::PRESS  }},
    };
}

omni::types::Vec2f omniscia::core::Controls::get_mouse() {
    return _mousePos;
}

bool omniscia::core::Controls::get(const PlayerController& action) {
    return controlStates[action];
}

bool omniscia::core::Controls::get(const MouseController& action) {
    return controlStates[action];
}

void omniscia::core::Controls::handle_input(GLFWwindow *window) {

    std::unordered_map<i32, std::pair<i32, ActionType>>::const_iterator keyIterator;
    for(keyIterator = keyBindigs.begin(); keyIterator != keyBindigs.end(); ++keyIterator) {
        const auto key = *keyIterator; 
        const ActionType& actionType = key.second.second;

        controlStates[key.second.first] = (glfwGetKey(window, key.first) == actionType);
    }

    std::unordered_map<i32, std::pair<i32, ActionType>>::const_iterator mouseIterator;
    for(mouseIterator = mouseBindigs.begin(); mouseIterator != mouseBindigs.end(); ++mouseIterator) {
        const auto key = *mouseIterator; 
        const ActionType& actionType = key.second.second;

        controlStates[key.second.first] = (glfwGetMouseButton(window, key.first) == actionType);
    }

    f64 xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    _mousePos.x = 2.0f * (xpos / Properties::get_instance().screenWidth) - 1.0f;
    _mousePos.y = 2.0f * (ypos / Properties::get_instance().screenHeight) - 1.0f;
    _mousePos.x *= Properties::get_instance().screenWidth / (f32)Properties::get_instance().screenHeight;
    _mousePos.y = -_mousePos.y;
}
