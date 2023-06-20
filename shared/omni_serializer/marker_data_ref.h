#ifndef _MARKER_DATA_REF_H_
#define _MARKER_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    // using namespace omni::reflector::serialization;

    struct MarkerData : Reflected<MarkerData> {
        Vec2f _position;

        const constexpr static auto meta = std::make_tuple(
            field(_position)
        );
    };
}

#endif
