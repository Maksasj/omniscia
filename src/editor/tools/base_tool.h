#ifndef _OMNISCIA_EDITOR_BASE_TOOL_H_
#define _OMNISCIA_EDITOR_BASE_TOOL_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "windows/history_window.h"

namespace omniscia_editor::tools {
    using namespace omniscia_editor::windows;

    struct BaseTool {
        virtual void render_effect() {}
    };
}

#endif
