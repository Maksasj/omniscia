#ifndef _OMNISCIA_EDITOR_COLOR_PICKER_H_
#define _OMNISCIA_EDITOR_COLOR_PICKER_H_

#include <string>

#include "gfx.h"
#include "types.h"

namespace omniscia_editor::level_editor {
    using namespace omni::types;

    void color_picker(std::string _label, ImVec4& colorTarget);
}

#endif
