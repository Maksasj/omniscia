#ifndef _OMNISCIA_EDITOR_PENCIL_TOOL_H_
#define _OMNISCIA_EDITOR_PENCIL_TOOL_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "base_tool.h"

namespace omniscia_editor::tools {
    using namespace omni::types;

    class PencilTool : public BaseTool {
        public:
            bool _renderGhostTile;
            Vec4f _ghostTileColor;

            PencilTool();

            void render_effect() override;
            
            static PencilTool& get_instance();
    };
}

#endif
