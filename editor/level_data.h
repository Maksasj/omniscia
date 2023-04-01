#ifndef _OMNISCIA_EDITOR_LEVEL_DATA_H_
#define _OMNISCIA_EDITOR_LEVEL_DATA_H_

#include <vector>

#include "gfx.h"
#include "types.h"

namespace omniscia_editor::level_editor {
    struct TileGroup {
        std::string _name;
        ImVec4 _associatedColor;
        std::vector<omniscia::core::Vec2f> tiles;

        TileGroup(std::string name) : _name(name) {
            _associatedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    };

    struct LevelData {
        std::vector<TileGroup> tileGroups;

        LevelData() {

        }
    };
}

#endif
