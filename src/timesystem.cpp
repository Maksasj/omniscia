#include "timesystem.h"

omni::types::f32 omniscia::core::Time::get_delta_time() {
    return _deltaTime * 1000.0;
}

void omniscia::core::Time::update_delta_time_clock() {
    _firstTime = glfwGetTime();
    _deltaTime = _firstTime - _secondTime;
    _secondTime = _firstTime;
}

omniscia::core::Time& omniscia::core::Time::get_instance() {
    static Time instace;
    return instace;
}
