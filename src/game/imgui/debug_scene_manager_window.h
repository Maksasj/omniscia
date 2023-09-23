#ifndef _DEBUG_SCENE_MANAGER_WINDOW_
#define _DEBUG_SCENE_MANAGER_WINDOW_

#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "omni_types.tpp"
#include "gfx/gfx.h"

#include "imgui/debug_info.h"
#include "imgui/debug_field_query.h"

#include "properties.h"

namespace omniscia::core {
    using namespace omni::types;

    class DebugSceneManagerWindow {
        private:
        public:
            void render();

            static DebugSceneManagerWindow& get_instance();
    };
}

#endif
