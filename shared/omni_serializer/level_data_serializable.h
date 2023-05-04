#ifndef _LEVEL_DATA_SERIALIZABLE_H_
#define _LEVEL_DATA_SERIALIZABLE_H_

#include "omni_serializer.h"

#include "serializable_string.tpp"
#include "tile_data_serializable.h"
#include "collisionbox_data_serializable.h"
#include "tilegroup_data_serializable.h"

namespace omni::serializer {
    struct SerializableLevelData : public core::Serializable {
        omni::serializer::Serializable<f32> _screenBoxWidth;
        omni::serializer::Serializable<f32> _screenBoxHeight;

        SerializableVector<SerializableTileGroupData> _tileGroups;

        public:
            void deserialize(std::istream &stream) override {
                _screenBoxWidth.deserialize(stream);
                _screenBoxHeight.deserialize(stream);
                
                _tileGroups.deserialize(stream);
            }
            
            void serialize(std::ostream &stream) override {
                _screenBoxWidth.serialize(stream);
                _screenBoxHeight.serialize(stream);
                
                _tileGroups.serialize(stream);
            }
    };
}

#endif