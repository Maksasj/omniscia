#ifndef _OMNISCIA_EDITOR_TILE_GROUP_DATA_H_
#define _OMNISCIA_EDITOR_TILE_GROUP_DATA_H_

#include <vector>
#include <algorithm>

#include "omni_serializer.h"
#include "level_data_serializable.h"
#include "collisionbox_data_serializable.h"

#include "../types.h"
#include "../image_loading.h"

namespace omniscia_editor::level_editor {
    using namespace omni::types;
    using namespace omni::serializer;

    struct TileGroup {
        char _name[256];
        Vec4f _associatedColor;
        std::vector<TileData> tiles;
        std::vector<CollisionBoxData> _collisionBoxes;

        bool _tileSetLoaded;
        i32 _tileSetImageWidth;
        i32 _tileSetImageHeight;
        GLuint _tileSetTexture;

        TileGroup(std::string name);

        void clear();
    };
}

#endif
