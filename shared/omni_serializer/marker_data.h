#ifndef _MARKER_DATA_REF_H_
#define _MARKER_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct MarkerData {
        Vec2f _position;
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, MarkerData, _position);

#endif
