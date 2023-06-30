#ifndef _COLLISIONBOX_DATA_REF_H_
#define _COLLISIONBOX_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"


namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct CollisionBoxEntity {
        std::string _name;

        Vec4f _collisionBoxAssociatedColor;
        
        Vec2f _position;
        Vec2f _xRanges;
        Vec2f _yRanges;

        bool _isDamaging;

        CollisionBoxEntity() {
            std::string _name = "Unnamed collision box";

            _collisionBoxAssociatedColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

            _position = Vec2f::splat(0.0f);
            _xRanges = Vec2f::splat(0.0f);
            _yRanges = Vec2f::splat(0.0f);

            _isDamaging = false;
        }

        CollisionBoxEntity(const std::string& name, const Vec2f& position, const Vec2f& rangesX, const Vec2f& rangesY) {
            _name = name;

            _collisionBoxAssociatedColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

            _position = position;
            _xRanges = rangesX;
            _yRanges = rangesY;

            _isDamaging = false;
        }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, CollisionBoxEntity, _name, _collisionBoxAssociatedColor, _position, _xRanges, _yRanges, _isDamaging);

#endif
