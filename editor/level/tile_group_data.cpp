#include "tile_group_data.h"

omniscia_editor::level_editor::TileGroup::TileGroup(std::string name) {
    _associatedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    name.copy(_name, ((name.size() > 256) ? 256 : name.size()));
}

void omniscia_editor::level_editor::TileGroup::clear() {
    tiles.clear();
    _collisionBoxes.clear();
}