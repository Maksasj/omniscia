#ifndef _TILEGROUP_DATA_SERIALIZABLE_H_
#define _TILEGROUP_DATA_SERIALIZABLE_H_

#include "omni_serializer.h"

#include "serializable_string.tpp"
#include "tile_data_serializable.h"
#include "collisionbox_data_serializable.h"

namespace omni::serializer {
    using namespace omni::types;

    struct SerializableTileGroupData : public core::Serializable {
        SerializableString _name;
        omni::serializer::Serializable<Vec4f> _tileGroupAssociatedColor;

        SerializableVector<SerializableTileData> _tiles;
        SerializableVector<SerializableCollisionBoxData> _collisionBoxes;

        void deserialize(std::istream &stream) override {
            _name.deserialize(stream);
            _tileGroupAssociatedColor.deserialize(stream);
            
            _tiles.deserialize(stream);
            _collisionBoxes.deserialize(stream);
        }
        
        void serialize(std::ostream &stream) override {
            _name.serialize(stream);
            _tileGroupAssociatedColor.serialize(stream);
            _tiles.serialize(stream);
            _collisionBoxes.serialize(stream);
        }
    };
}

#endif