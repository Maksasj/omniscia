#ifndef _OMNISCIA_EDITOR_TILE_DATA_H_
#define _OMNISCIA_EDITOR_TILE_DATA_H_

#include "../types.h"

namespace omniscia_editor::level_editor {
    struct Tile {
       f32 x;
       f32 y;

       f32 _width;
       f32 _height;
    };
}

#endif
