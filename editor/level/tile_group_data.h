#ifndef _OMNISCIA_EDITOR_TILE_GROUP_DATA_H_
#define _OMNISCIA_EDITOR_TILE_GROUP_DATA_H_

#include <vector>
#include <algorithm>

#include "collsion_box_data.h"
#include "tile_data.h"
#include "../types.h"
#include "../gfx.h"

namespace omniscia_editor::level_editor {
    struct TileGroup {
        char _name[256];
        ImVec4 _associatedColor;
        std::vector<Tile> tiles;
        std::vector<CollisionBox> _collisionBoxes;

        TileGroup(std::string name);

        void clear();
    };
}

#endif
