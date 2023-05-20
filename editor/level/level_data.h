#ifndef _OMNISCIA_EDITOR_LEVEL_DATA_H_
#define _OMNISCIA_EDITOR_LEVEL_DATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "omni_serializer.h"

#include "../level_editor_properties.h"

namespace omniscia_editor::level_editor {
    using namespace omni::types;
    using namespace omniscia::core;
    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    struct LevelData {
        std::vector<TileGroupData> _tileGroups;
        std::vector<MarkerGroupData> _markerGroups;

        void load_from_file(std::string filePath, LevelEditorProperties& levelEditorProperties);
        void export_to_file(std::string filePath, LevelEditorProperties& levelEditorProperties);
    };
}

#endif
