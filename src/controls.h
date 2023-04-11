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

#include "types.tpp"
#include "gfx.h"

namespace omniscia::core {
    /**
     * @brief Enum used to identify that 
     * action player wants to do
    */
    enum PlayerController {
        JUMP,
        DOWN,
        LEFT,
        RIGHT,
        TIME_JUMP,
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
            static std::unordered_map<PlayerController, bool> controlStates;

            /**
             * @brief Container that stores which keys binded to which actions
            */
            static std::unordered_map<u8, std::pair<PlayerController, ActionType>> keyBindigs;

        public:
            /**
             * @brief function that returns the state of the specific action
             * 
             * @param action type
             * @return true action is active
             * @return false action is not active
             */
            static bool get(const PlayerController& action);

            /**
             * @brief Method that updates states of all actions
             * 
             * @param window pointer to GLFWwindow stance
             */
            static void handle_input(GLFWwindow *window);
    };
}

#endif
