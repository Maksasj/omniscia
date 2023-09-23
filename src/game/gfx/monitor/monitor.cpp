#include "gfx/monitor/monitor.h"

omniscia::gfx::monitor::Monitor* omniscia::gfx::monitor::Monitor::_activeMonitor = nullptr;

omniscia::gfx::monitor::Monitor::Monitor(GLFWmonitor* glfwMonitor) {
    _glfwMonitor = glfwMonitor;

    glfwGetMonitorWorkarea(_glfwMonitor, &_monitorPos.x, &_monitorPos.y, &_monitorSize.x, &_monitorSize.y);
    _monitorName = glfwGetMonitorName(_glfwMonitor);
}

omniscia::gfx::monitor::Monitor* omniscia::gfx::monitor::Monitor::get_active() {
    return _activeMonitor;
}

std::vector<omniscia::gfx::monitor::Monitor*> omniscia::gfx::monitor::Monitor::retrieve_monitors() {
    static std::vector<Monitor*> monitors;
    monitors.clear();

    i32 glfwMonitorCount = 0;
    GLFWmonitor** glfwMonitors = glfwGetMonitors(&glfwMonitorCount);

    if(glfwMonitors == nullptr)
        throw std::runtime_error("Failed to retrieve monitors");

    if(glfwMonitorCount <= 0)
        throw std::runtime_error("Not found any monitors");

    for(auto i = 0; i < glfwMonitorCount; ++i)
        monitors.push_back(new Monitor(glfwMonitors[i]));

    return monitors;
}

void omniscia::gfx::monitor::Monitor::set_active() {
    _activeMonitor = this;
}

std::string omniscia::gfx::monitor::Monitor::get_name() const {
    return _monitorName;
}

omni::types::Vec2i omniscia::gfx::monitor::Monitor::get_pos() const {
    return _monitorPos;
}

omni::types::Vec2i omniscia::gfx::monitor::Monitor::get_size() const {
    return _monitorSize;
}

GLFWmonitor* omniscia::gfx::monitor::Monitor::get_glfw_monitor() {
    return _glfwMonitor;
}
