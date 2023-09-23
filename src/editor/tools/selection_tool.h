#ifndef _OMNISCIA_EDITOR_SELECTION_TOOL_H_
#define _OMNISCIA_EDITOR_SELECTION_TOOL_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "base_tool.h"

namespace omniscia_editor::tools {
    using namespace omni::types;

    class SelectionTool : public BaseTool {
        private:
            Vec2f _startPos;
            Vec4f _selectionColor;
            
        public:
            SelectionTool();

            void render_effect() override;
            
            static SelectionTool& get_instance();
    };
}

#endif
