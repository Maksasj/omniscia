#ifndef _OMNISCIA_MONITOR_H_
#define _OMNISCIA_MONITOR_H_

#include <vector>

#include "omni_types.tpp"
#include "gfx.h"

namespace omniscia::gfx::monitor {
    using namespace omni::types;

    class Monitor {
        private:    
            GLFWmonitor* _glfwMonitor;
            std::string _monitorName;
            Vec2i _monitorSize;
            Vec2i _monitorPos;

            static Monitor* _activeMonitor;

            Monitor(GLFWmonitor* glfwMonitor);

        public:
            GLFWmonitor* get_glfw_monitor();
            
            std::string get_name() const;
            Vec2i get_pos() const;
            Vec2i get_size() const;
            void set_active();

            static std::vector<Monitor*> retrieve_monitors();

            static Monitor* get_active();
    };
}

#endif
