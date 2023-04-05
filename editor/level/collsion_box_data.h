#ifndef _OMNISCIA_EDITOR_COLLISION_BOX_DATA_H_
#define _OMNISCIA_EDITOR_COLLISION_BOX_DATA_H_

#include <string>
#include "../types.h"
#include "../gfx.h"

namespace omniscia_editor::level_editor {
    struct CollisionBox {
        char _name[256] = {};
        ImVec4 _associatedColor;

        f32 _x;
        f32 _y;

        omniscia::core::Vec2f _rangesX;
        omniscia::core::Vec2f _rangesY;

        CollisionBox() {
            
        }

        CollisionBox(std::string name, f32 x, f32 y, omniscia::core::Vec2f rangesX, omniscia::core::Vec2f rangesY) {
            name.copy(_name, name.size());

            _x = x;
            _y = y;

            _rangesX = rangesX;
            _rangesY = rangesY;

            _associatedColor = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
        }
    };
}

#endif
