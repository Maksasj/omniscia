#ifndef _TILEGROUP_DATA_REF_H_
#define _TILEGROUP_DATA_REF_H_

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#include "omni_types.tpp"

#include "tile_data_ref.h"
#include "collisionbox_data_ref.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;
    // using namespace omni::reflector::serialization;

    struct TileGroupData : Reflected<TileGroupData> {
        std::string _name;
        Vec4f _tileGroupAssociatedColor = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};

        std::vector<TileData> _tiles;
        std::vector<CollisionBoxData> _collisionBoxes;

        // Editor only
        bool _tileSetLoaded;
        i32 _tileSetImageWidth;
        i32 _tileSetImageHeight;
        u32 _tileSetTexture;

        TileGroupData() {}
        
        TileGroupData(const std::string& name) {
            _name = name;
        }

        const constexpr static auto meta = std::make_tuple(
            field(_name),
            field(_tileGroupAssociatedColor),
            field(_tiles),
            field(_collisionBoxes)
        );
    };
}

#endif
