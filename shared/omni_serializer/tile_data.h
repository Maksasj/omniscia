#ifndef _TILE_DATA_REF_H_
#define _TILE_DATA_REF_H_

#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    struct TileEntity {
        Vec2f _position;
        i32 _materialId;

        /* Editor only */
        bool _selected = false;
    };
}

template<>
struct omni::reflector::Reflection<omniscia::core::TileEntity> {
    const constexpr static std::type_info &typeInfo = typeid(omniscia::core::TileEntity);
    const constexpr static auto clearTypeName = "TileEntity";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia::core::TileEntity::_position, "p"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia::core::TileEntity::_materialId, "m")
    );																		                
};	

#endif
