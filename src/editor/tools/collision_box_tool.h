#ifndef _OMNISCIA_EDITOR_COLLISION_BOX_TOOL_H_
#define _OMNISCIA_EDITOR_COLLISION_BOX_TOOL_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "base_tool.h"

namespace omniscia_editor::tools {
    using namespace omni::types;

    class CollisionBoxTool : public BaseTool {
        private:
            Vec2f _startPos;
            Vec4f _selectionColor;

            bool _renderFilledCollisionBoxGhost;
            
        public:
            CollisionBoxTool();

            void render_effect() override;
            
            static CollisionBoxTool& get_instance();
    };
}

#endif
