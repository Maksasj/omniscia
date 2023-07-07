#ifndef _DEBUG_METRICS_WINDOW_
#define _DEBUG_METRICS_WINDOW_

#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "omni_types.tpp"
#include "gfx/gfx.h"

#include "imgui/debug_info.h"

namespace omniscia::core {
    using namespace omni::types;

    class DebugMetricsWindow {
        private:
        public:
            void render();

            static DebugMetricsWindow& get_instance();
    };
}

#endif
