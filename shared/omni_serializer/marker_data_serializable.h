#ifndef _MARKER_DATA_SERIALIZABLE_H_
#define _MARKER_DATA_SERIALIZABLE_H_

#include "omni_serializer.h"

namespace omni::serializer {
    using namespace omni::types;
    
    struct SerializableMarkerData : public core::Serializable {
        omni::serializer::Serializable<Vec2f> _position;

        public:
            void deserialize(std::istream &stream) override {
                _position.deserialize(stream);
            }
            
            void serialize(std::ostream &stream) override {
                _position.serialize(stream);
            }
    };
}

#endif