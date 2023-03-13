#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include <GLFW/glfw3.h>
#include <iostream>

#include "unordered_map"

#include "types.h"

namespace omniscia::core {
    enum PlayerController {
        JUMP,
        LEFT,
        RIGHT
    };

    /*
     * Todo generalize this fingi for different controllers, akka templates
    */

    class Controls {
        static std::unordered_map<PlayerController, bool> controlStates;
        static std::unordered_map<u8, PlayerController> keyBindigs;

        public:
            static bool get(const PlayerController& action);
            static void handle_input(GLFWwindow *window);
    };
}

#endif
