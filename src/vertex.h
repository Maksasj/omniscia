#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <glad/glad.h>

#include "types.h"

namespace omniscia::renderer {
    using namespace omniscia::core;

    struct Vertex {
        Vec3f pos;
        Vec3f color;
        Vec2f texPos;

        Vertex(Vec3f _pos, Vec3f _color, Vec2f _texPos) {
            pos = _pos;
            color = _color;
            texPos = _texPos;
        }
    };
}

#endif