#ifndef _MARKERGROUP_DATA_REF_H_
#define _MARKERGROUP_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

#include "marker_data.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct MarkerGroupData {
        Vec4f _markerGroupAssociatedColor;
        
        std::vector<MarkerData> _markers;

        MarkerGroupData() {
            _markerGroupAssociatedColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
        }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, MarkerGroupData, _markerGroupAssociatedColor, _markers);

#endif
