#ifndef _OMNISCIA_EDITOR_COLLISION_BOX_DATA_H_
#define _OMNISCIA_EDITOR_COLLISION_BOX_DATA_H_

#include "../types.h"

namespace omniscia_editor::level_editor {
    struct CollisionBox {
        f32 x;
        f32 y;

        omniscia::core::Vec2f rangesX;
        omniscia::core::Vec2f rangesY;
    };
}

#endif
