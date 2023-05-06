#ifndef _OMNISCIA_EDITOR_LEVEL_DATA_H_
#define _OMNISCIA_EDITOR_LEVEL_DATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "omni_serializer.h"
#include "level_data_serializable.h"
#include "collisionbox_data_serializable.h"

#include "../level_editor_properties.h"

namespace omniscia_editor::level_editor {
    using namespace omni::types;
    using namespace omni::serializer;

    struct LevelData {
        SerializableVector<SerializableTileGroupData> _tileGroups;
        SerializableVector<SerializableMarkerGroupData> _markerGroups;

        void load_from_file(std::string filePath, LevelEditorProperties& levelEditorProperties);
        void export_to_file(std::string filePath, LevelEditorProperties& levelEditorProperties);
    };
}

#endif
