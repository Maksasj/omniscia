#include "controls.h"

std::unordered_map<omniscia::core::PlayerController, bool> omniscia::core::Controls::controlStates = {
    {omniscia::core::PlayerController::JUMP,    false},
    {omniscia::core::PlayerController::LEFT,    false},
    {omniscia::core::PlayerController::RIGHT,   false}
};

std::unordered_map<u8, omniscia::core::PlayerController> omniscia::core::Controls::keyBindigs = {
    {'w', omniscia::core::PlayerController::JUMP},
    {'a', omniscia::core::PlayerController::LEFT},
    {'d', omniscia::core::PlayerController::RIGHT}
};

void omniscia::core::Controls::handle_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    for(auto &key : keyBindigs) {
        if (glfwGetKey(window, key.first) == GLFW_PRESS) {
            controlStates[key.second] = true;
        } else {
            controlStates[key.second] = false;
        }
    }
}
