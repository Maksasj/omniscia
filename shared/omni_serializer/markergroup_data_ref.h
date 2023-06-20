#ifndef _MARKERGROUP_DATA_REF_H_
#define _MARKERGROUP_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

#include "marker_data_ref.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    // using namespace omni::reflector::serialization;

    struct MarkerGroupData : Reflected<MarkerGroupData> {
        Vec4f _markerGroupAssociatedColor = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        std::vector<MarkerData> _markers;

        const constexpr static auto meta = std::make_tuple(
            field(_markerGroupAssociatedColor),
            field(_markers)
        );
    };
}

#endif
