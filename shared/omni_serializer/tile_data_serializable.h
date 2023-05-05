#ifndef _TILE_DATA_SERIALIZABLE_H_
#define _TILE_DATA_SERIALIZABLE_H_

#include "types.tpp"

#include "omni_serializer.h"

namespace omni::serializer {
    using namespace omni::types;

    struct TileData {
        Vec2f _position;
        Vec2f _scale;

        Vec2f _textureCordsTopRight      = {1.0f, 1.0f};
        Vec2f _textureCordsBottomRight   = {1.0f, 0.0f};
        Vec2f _textureCordsBottomLeft    = {0.0f, 1.0f};
        Vec2f _textureCordsTopLeft       = {0.0f, 0.0f};
    };

    struct SerializableTileData : public Serializable<TileData> {
        private:

        public:
            SerializableTileData() : Serializable() {}
            SerializableTileData(const TileData& value) : Serializable(value) {}
    };
}

#endif