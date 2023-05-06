#ifndef _MARKERROUP_DATA_SERIALIZABLE_H_
#define _MARKERROUP_DATA_SERIALIZABLE_H_

#include "omni_serializer.h"

#include "marker_data_serializable.h"

namespace omni::serializer {
    using namespace omni::types;

    struct SerializableMarkerGroupData : public core::Serializable {
        omni::serializer::Serializable<Vec4f> _markerGroupAssociatedColor = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        SerializableVector<SerializableMarkerData> _markers;

        void deserialize(std::istream &stream) override {
            _markerGroupAssociatedColor.deserialize(stream);
            _markers.deserialize(stream);
        }
        
        void serialize(std::ostream &stream) override {
            _markerGroupAssociatedColor.serialize(stream);
            _markers.serialize(stream);
        }
    };
}

#endif