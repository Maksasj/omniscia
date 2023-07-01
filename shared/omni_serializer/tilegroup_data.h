#ifndef _TILEGROUP_DATA_REF_H_
#define _TILEGROUP_DATA_REF_H_

#include <string>
#include <vector>

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

#include "tile_material.h"
#include "tile_data.h"
#include "collisionbox_data.h"

namespace omniscia::core {
    using namespace std;

    using namespace omni::types;
    using namespace omni::reflector;

    struct TileGroupData {
        string _name;
        Vec4f _tileGroupAssociatedColor;

        string _textureMaterialAssetId;

        vector<TileMaterial> _tileMaterials;
        vector<TileEntity> _tiles;

        vector<CollisionBoxEntity> _collisionBoxes;

        TileGroupData() {
            _name = "Unnamed tile group";

            _tileGroupAssociatedColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

            _textureMaterialAssetId = "";

            _tileMaterials.push_back(TileMaterial::default_material());
        };

        TileGroupData(const string& name) { 
            _name = name;

            _tileGroupAssociatedColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

            _textureMaterialAssetId = "";

            _tileMaterials.push_back(TileMaterial::default_material());
        }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, TileGroupData, _name, _tileGroupAssociatedColor, _textureMaterialAssetId, _tileMaterials, _tiles, _collisionBoxes);

#endif
