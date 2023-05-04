#ifndef _TILE_DATA_SERIALIZABLE_H_
#define _TILE_DATA_SERIALIZABLE_H_

#include "types.tpp"

#include "omni_serializer.h"

namespace omni::serializer {
    using namespace omniscia::core;

    struct TileData {
        omniscia::core::Vec2f _position;
        omniscia::core::Vec2f _scale;

        omniscia::core::Vec2f _textureCordsTopRight      = {1.0f, 1.0f};
        omniscia::core::Vec2f _textureCordsBottomRight   = {1.0f, 0.0f};
        omniscia::core::Vec2f _textureCordsBottomLeft    = {0.0f, 1.0f};
        omniscia::core::Vec2f _textureCordsTopLeft       = {0.0f, 0.0f};
    };

    struct SerializableTileData : public Serializable<TileData> {
        private:

        public:
            SerializableTileData() : Serializable() {}
            SerializableTileData(const TileData& value) : Serializable(value) {}
    };
}

#endif