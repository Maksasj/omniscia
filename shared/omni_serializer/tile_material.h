#ifndef _TILE_MATERIAL_H_
#define _TILE_MATERIAL_H_

#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct TileMaterial {
        std::string _materialName;

        Vec2f _scale;

        Vec2f _textureCordsTopRight;
        Vec2f _textureCordsBottomRight;
        Vec2f _textureCordsBottomLeft;
        Vec2f _textureCordsTopLeft;

        TileMaterial() {
            *this = default_material();
        }

        TileMaterial(const std::string& materialName, const Vec2f& scale, const Vec2f& _texTR, const Vec2f& _texBR, const Vec2f& _texBL, const Vec2f& _texTL) {
            _materialName = materialName;
            
            _scale = scale;

            _textureCordsTopRight = _texTR;
            _textureCordsBottomRight = _texBR;
            _textureCordsBottomLeft = _texBL;
            _textureCordsTopLeft = _texTL;
        }

        static TileMaterial default_material() {
            return TileMaterial(
                "Default material", 
                Vec2f::splat(1.0f), 
                Vec2f::splat(1.0f), 
                Vec2f(1.0f, 0.0f), 
                Vec2f(0.0f, 1.0f), 
                Vec2f::splat(0.0f)
            );
        }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, TileMaterial, _materialName, _scale, _textureCordsTopRight, _textureCordsBottomRight, _textureCordsBottomLeft, _textureCordsTopLeft);

#endif
