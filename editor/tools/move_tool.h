#ifndef _OMNISCIA_EDITOR_MOVE_TOOL_H_
#define _OMNISCIA_EDITOR_MOVE_TOOL_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "base_tool.h"

namespace omniscia_editor::tools {
    using namespace omni::types;

    class MoveTool : public BaseTool {
        private:
            bool _gridSnaping;

            Vec2f _movedPosition;

        public:
            MoveTool();

            void render_effect() override;
            
            static MoveTool& get_instance();
    };
}

#endif
