#ifndef _TILE_DATA_REF_H_
#define _TILE_DATA_REF_H_

#include "types.tpp"

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    struct TileData {
        Vec2f _position;
        Vec2f _scale;

        Vec2f _textureCordsTopRight      = {1.0f, 1.0f};
        Vec2f _textureCordsBottomRight   = {1.0f, 0.0f};
        Vec2f _textureCordsBottomLeft    = {0.0f, 1.0f};
        Vec2f _textureCordsTopLeft       = {0.0f, 0.0f};
    };
}

#endif
