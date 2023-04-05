#ifndef _OMNISCIA_EDITOR_LEVEL_DATA_H_
#define _OMNISCIA_EDITOR_LEVEL_DATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../level_editor_properties.h"
#include "tile_group_data.h"

namespace omniscia_editor::level_editor {
    struct LevelData {
        std::vector<TileGroup> tileGroups;

        LevelData();

        void load_from_file(std::string filePath, LevelEditorProperties& levelEditorProperties);
        void export_to_file(std::string filePath, LevelEditorProperties& levelEditorProperties);
    };
}

#endif
