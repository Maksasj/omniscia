#ifndef _COLLISIONBOX_DATA_REF_H_
#define _COLLISIONBOX_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"


namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct CollisionBoxData : Reflected<CollisionBoxData> {
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

        const constexpr static auto meta = std::make_tuple(
            field(_name),
            field(_collisionBoxAssociatedColor),
            field(_position),
            field(_xRanges),
            field(_yRanges),
            field(_isDamaging)
        );
    };
}

#endif
