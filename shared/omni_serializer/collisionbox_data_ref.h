#ifndef _COLLISIONBOX_DATA_REF_H_
#define _COLLISIONBOX_DATA_REF_H_

#include "types.tpp"

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

struct byte256 {
    char _bytes[256];

    friend std::ostream& operator<<(std::ostream& os, const byte256& vec) {
        for(int i = 0; i < 256; ++i)
            os << vec._bytes[i];

        return os;
    }
};

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    struct CollisionBoxData {
        byte256 _name;
        Vec4f _collisionBoxAssociatedColor;
        Vec2f _position;
        Vec2f _xRanges;
        Vec2f _yRanges;

        bool _isDamaging;

        CollisionBoxData() {
            std::string name = "poggers";
            name.copy(_name._bytes, name.size());
        }

        CollisionBoxData(std::string name, f32 x, f32 y, Vec2f rangesX, Vec2f rangesY) {
            name.copy(_name._bytes, name.size());

            _position.x = x;
            _position.y = y;

            _xRanges = rangesX;
            _yRanges = rangesY;

            _isDamaging = false;

            _collisionBoxAssociatedColor = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        }
    };
}

#endif
