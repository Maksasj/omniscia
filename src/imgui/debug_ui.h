/**
 * @file 
 * debug_ui.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _DEBUG_GUI_
#define _DEBUG_GUI_

#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "types.tpp"
#include "gfx.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief DebugUI - singleton class used for debugging, and collecting different metrics across entire game
    */
    class DebugUI {
        private:
            /**
             * @brief DebugMetrics - class that stores diffrent metrics
            */
            struct DebugMetrics {
                /** @brief How much milliseconds code that manipulates time line is took executing */
                f32 _timeManipulationTime;
                
                /** @brief Time line length */
                u64 _timeCurrentLineLength;
                
                /** @brief Time max line length */
                u64 _timeMaxLineLength;

                /** @brief How much sounds is currently playing */
                i32 _currentlyPlayingSoundCount;
                
                /** @brief Is game in time jump mode */
                bool _isTimeJump;

                bool _systemInterupt;

                /** @brief Current player position */
                Vec2f _playerPos;

                Vec2f _cameraPos;
            };

            /** @brief Pointer to imgui io */
            ImGuiIO* _imgui_io;    

            /** @brief Metrics it self */
            DebugMetrics _metrics;

            /** @brief Hidden constructor */
            DebugUI() : _imgui_io(nullptr) {};
            
            /** @brief Hidden copy constructor */
            DebugUI(DebugUI const&) {};
            
            /** @brief Hidden assignment operator */
            void operator=(DebugUI const&) {};

        public:
            /**
             * @brief Initializes DebugUI instance
             * 
             * @param window pointer to GLFW windows instance 
            */
            void init(GLFWwindow* window);

            /**
             * @brief Renders DebugUI on to the screen
            */
            void render();
            
            /**
             * @brief References current metrics object
             * 
             * @return reference to the metrics object instance
             */
            DebugMetrics& get_metrics();
            
            /**
             * @brief Get the singleton instance of the DebugUI
             * 
             * @return Reference to singleton instance of the DebugUI
            */
            static DebugUI& get_instance();
    };
}

#endif
