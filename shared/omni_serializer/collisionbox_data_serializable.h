#ifndef _COLLISIONBOX_DATA_SERIALIZABLE_H_
#define _COLLISIONBOX_DATA_SERIALIZABLE_H_

#include "types.tpp"

#include "omni_serializer.h"

namespace omni::serializer {
    using namespace omni::types;

    struct CollisionBoxData {
        char _name[256];
        Vec4f _collisionBoxAssociatedColor;
        Vec2f _position;
        Vec2f _xRanges;
        Vec2f _yRanges;

        CollisionBoxData() {
            std::string name = "poggers";
            name.copy(_name, name.size());
        }

        CollisionBoxData(std::string name, f32 x, f32 y, Vec2f rangesX, Vec2f rangesY) {
            name.copy(_name, name.size());

            _position.x = x;
            _position.y = y;

            _xRanges = rangesX;
            _yRanges = rangesY;

            _collisionBoxAssociatedColor = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        }
    };

    class SerializableCollisionBoxData : public Serializable<CollisionBoxData> {
        private:

        public:
            SerializableCollisionBoxData() : Serializable() {}
            SerializableCollisionBoxData(const CollisionBoxData& value) : Serializable(value) {}
    };
}

#endif