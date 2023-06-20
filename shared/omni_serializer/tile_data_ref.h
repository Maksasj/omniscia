#ifndef _TILE_DATA_REF_H_
#define _TILE_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    // using namespace omni::reflector::serialization;

    struct TileData : Reflected<TileData> {
        Vec2f _position;
        Vec2f _scale;

        Vec2f _textureCordsTopRight      = {1.0f, 1.0f};
        Vec2f _textureCordsBottomRight   = {1.0f, 0.0f};
        Vec2f _textureCordsBottomLeft    = {0.0f, 1.0f};
        Vec2f _textureCordsTopLeft       = {0.0f, 0.0f};

        const constexpr static auto meta = std::make_tuple(
            field(_position),
            field(_scale),

            field(_textureCordsTopRight),
            field(_textureCordsBottomRight),
            field(_textureCordsBottomLeft),
            field(_textureCordsTopLeft)
        );
    };
}

#endif
