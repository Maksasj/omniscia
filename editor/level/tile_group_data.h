#ifndef _OMNISCIA_EDITOR_TILE_GROUP_DATA_H_
#define _OMNISCIA_EDITOR_TILE_GROUP_DATA_H_

#include <vector>

#include "tile_data.h"
#include "../types.h"
#include "../gfx.h"

namespace omniscia_editor::level_editor {
    struct TileGroup {
        std::string _name;
        ImVec4 _associatedColor;
        std::vector<Tile> tiles;

        TileGroup(std::string name);
    };
}

#endif
