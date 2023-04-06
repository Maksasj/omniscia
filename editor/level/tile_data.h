#ifndef _OMNISCIA_EDITOR_TILE_DATA_H_
#define _OMNISCIA_EDITOR_TILE_DATA_H_

#include "../types.h"

namespace omniscia_editor::level_editor {
    struct Tile {
        f32 x;
        f32 y;

        f32 _width;
        f32 _height;

        omniscia::core::Vec2f textureCordsTopRight      = {1.0f, 1.0f};
        omniscia::core::Vec2f textureCordsBottomRight   = {1.0f, 0.0f};
        omniscia::core::Vec2f textureCordsBottomLeft    = {0.0f, 1.0f};
        omniscia::core::Vec2f textureCordsTopLeft       = {0.0f, 0.0f};
    };
}

#endif
