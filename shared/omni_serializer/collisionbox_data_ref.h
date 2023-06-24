#ifndef _COLLISIONBOX_DATA_REF_H_
#define _COLLISIONBOX_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"


namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct CollisionBoxData {
        std::string _name;
        Vec4f _collisionBoxAssociatedColor;
        Vec2f _position;
        Vec2f _xRanges;
        Vec2f _yRanges;

        bool _isDamaging;

        CollisionBoxData() {
            std::string _name = "poggers";
        }

        CollisionBoxData(std::string name, f32 x, f32 y, Vec2f rangesX, Vec2f rangesY) {
            _name = name;

            _position.x = x;
            _position.y = y;

            _xRanges = rangesX;
            _yRanges = rangesY;

            _isDamaging = false;

            _collisionBoxAssociatedColor = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, CollisionBoxData, _name, _collisionBoxAssociatedColor, _position, _xRanges, _yRanges, _isDamaging);

#endif
