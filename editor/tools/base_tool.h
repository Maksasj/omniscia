#ifndef _OMNISCIA_EDITOR_BASE_TOOL_H_
#define _OMNISCIA_EDITOR_BASE_TOOL_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::tools {
    struct BaseTool {
        virtual void render_effect() {}
    };


    struct PencilTool : public BaseTool {
        void render_effect() override {

        }
        
        static PencilTool& get_instance() {
            static PencilTool tool;
            return tool;
        }
    };
}

#endif
