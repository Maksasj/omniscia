#include "tile_group_data.h"

omniscia_editor::level_editor::TileGroup::TileGroup(std::string name) : _name(name) {
    _associatedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}
