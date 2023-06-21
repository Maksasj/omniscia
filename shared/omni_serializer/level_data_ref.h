#ifndef _LEVEL_DATA_REF_H_
#define _LEVEL_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

#include "tilegroup_data_ref.h"
#include "markergroup_data_ref.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    struct LevelData : Reflected<LevelData> {
        f32 _screenBoxWidth;
        f32 _screenBoxHeight;

        std::vector<TileGroupData> _tileGroups;
        std::vector<MarkerGroupData> _markerGroups;

        const constexpr static auto meta = std::make_tuple(
            field(_screenBoxWidth),
            field(_screenBoxHeight),
            field(_tileGroups),
            field(_markerGroups)
        );
    };
}

#endif