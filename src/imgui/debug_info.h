/**
 * @file 
 * debug_info.h
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

#include "omni_types.tpp"
#include "gfx.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief DebugInfo - singleton class used for debugging, and collecting different metrics across entire game
    */
    class DebugInfo {
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

                bool _debugUIEnabled = false;
            };

            /** @brief Metrics it self */
            DebugMetrics _metrics;

            /** @brief Hidden constructor */
            DebugInfo() {};
            
            /** @brief Hidden copy constructor */
            DebugInfo(DebugInfo const&) {};
            
            /** @brief Hidden assignment operator */
            void operator=(DebugInfo const&) {};

        public:
            friend class DebugMetricsWindow;
            friend class DebugSceneManagerWindow;

            /**
             * @brief References current metrics object
             * 
             * @return reference to the metrics object instance
             */
            DebugMetrics& get_metrics();
            
            /**
             * @brief Get the singleton instance of the DebugInfo
             * 
             * @return Reference to singleton instance of the DebugInfo
            */
            static DebugInfo& get_instance();
    };
}

#endif
