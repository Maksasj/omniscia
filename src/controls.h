/**
 * @file 
 * controls.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include <iostream>
#include <unordered_map>

#include "properties.h"
#include "omni_types.tpp"
#include "gfx.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Enum used to identify that 
     * action player wants to do
    */
    enum PlayerController {
        JUMP = 0, DOWN = 1, LEFT = 2, RIGHT = 3,
        TIME_JUMP = 4, INTERACT = 5,
        PAUSE = 6,
        DEBUGUI = 7,
    };

    enum MouseController {
        LEFT_CLICK = 8,
        RIGHT_CLICK = 9,
    };
    
    /**
     * @brief Enum used to identify that button
     * action type player wants presses
    */
    enum ActionType {
        RELEASE,
        PRESS,
        REPEAT
    };

    /*
     * Todo generalize this fingi for different controllers, akka templates
    */

    /**
     * @brief Controls - singleton class 
     * used for managin player keyboard input
    */
    class Controls {
        private:
            /**
             * @brief Container that stores states of available actions
            */
            std::unordered_map<i32, bool> controlStates;

            /**
             * @brief Container that stores which keys binded to which actions
            */
            std::unordered_map<i32, std::pair<i32, ActionType>> keyBindigs;
            std::unordered_map<i32, std::pair<i32, ActionType>> mouseBindigs;

            Vec2f _mousePos;
            

            Controls();
            Controls(const Controls&) {}
            void operator=(const Controls&) {}

        public:
            /**
             * @brief function that returns the state of the specific action
             * 
             * @param action type
             * @return true action is active
             * @return false action is not active
             */
            bool get(const PlayerController& action);
            bool get(const MouseController& action);

            Vec2f get_mouse();

            /**
             * @brief Method that updates states of all actions
             * 
             * @param window pointer to GLFWwindow stance
             */
            void handle_input(GLFWwindow *window);

            static Controls& get_instance() {
                static Controls controls;
                return controls;
            }
    };
}

#endif
