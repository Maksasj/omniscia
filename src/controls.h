#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include <GLFW/glfw3.h>
#include <iostream>

#include "unordered_map"

#include "types.h"

namespace omniscia::core {
    enum PlayerController {
        JUMP,
        DOWN,
        LEFT,
        RIGHT,
        TIME_JUMP,
    };

    enum ActionType {
        RELEASE,
        PRESS,
        REPEAT
    };

    /*
     * Todo generalize this fingi for different controllers, akka templates
    */

    class Controls {
        static std::unordered_map<PlayerController, bool> controlStates;
        static std::unordered_map<u8, std::pair<PlayerController, ActionType>> keyBindigs;

        public:
            static bool get(const PlayerController& action);
            static void handle_input(GLFWwindow *window);

            //TODO, this is default glfw callback function from examples
            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
}

#endif
