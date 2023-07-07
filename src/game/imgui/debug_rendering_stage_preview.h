#ifndef _DEBUG_RENDERING_STAGE_PREVIEW_
#define _DEBUG_RENDERING_STAGE_PREVIEW_

#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "omni_types.tpp"
#include "gfx.h"

#include "debug_info.h"
#include "debug_field_query.h"

#include "properties.h"

namespace omniscia::core {
    using namespace omni::types;

    class DebugRenderingStagePreview {
        private:
        public:
            void render();

            static DebugRenderingStagePreview& get_instance();
    };
}

#endif
