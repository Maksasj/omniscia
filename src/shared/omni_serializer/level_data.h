#ifndef _LEVEL_DATA_REF_H_
#define _LEVEL_DATA_REF_H_

#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

#include "tilegroup_data.h"
#include "markergroup_data.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct LevelData {
        f32 _screenBoxWidth;
        f32 _screenBoxHeight;

        std::vector<TileGroupData> _tileGroups;
        std::vector<MarkerGroupData> _markerGroups;
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, LevelData, _screenBoxWidth, _screenBoxHeight, _tileGroups, _markerGroups);

#endif
