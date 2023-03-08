#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <glad/glad.h>
#include <sstream>

#include "types.h"

namespace omniscia::renderer {
    using namespace omniscia::core;

    struct Vertex {
        Vec3f pos;
        Vec3f color;
        Vec2f texPos;

        Vertex(const Vec3f& _pos, const Vec3f& _color, const Vec2f& _texPos) {
            pos = _pos;
            color = _color;
            texPos = _texPos;
        }

        void scale(const Vec3f& scale) {
            pos.x *= scale.x;
            pos.y *= scale.y;
            pos.z *= scale.z;
        }

        std::string to_string() {
            std::stringstream ss;

            ss << pos.x << ' ' << pos.y << ' ' << pos.z << ' ';
            ss << color.x << ' ' << color.y << ' ' << color.z << ' ';
            ss << texPos.x << ' ' << texPos.y;

            return ss.str();
        }
    };
}

#endif