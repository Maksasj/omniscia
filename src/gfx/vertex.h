#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <sstream>

#include "types.tpp"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omniscia::core;

    struct Vertex {
        Vec3f _pos;
        Vec3f _color;
        Vec2f _texPos;

        Vertex(const Vec3f& pos, const Vec3f& color, const Vec2f& texPos) {
            _pos = pos;
            _color = color;
            _texPos = texPos;
        }

        void scale(const Vec3f& scale) {
            _pos.x *= scale.x;
            _pos.y *= scale.y;
            _pos.z *= scale.z;
        }

        void transform(const Vec3f& pos = Vec3f{0.0f, 0.0f, 0.0f}) {
            _pos += pos;
        }

        void rotate(const f32& angle) {
            auto mat = Matrix<f32, 2, 2>::get_rotation_matrix(angle);

            _pos.x = _pos.x * mat.e[0] - _pos.y * mat.e[1];
            _pos.y = _pos.x * mat.e[2] + _pos.y * mat.e[3];
        }

        std::string to_string() {
            std::stringstream ss;

            ss << _pos.x << ' ' << _pos.y << ' ' << _pos.z << ' ';
            ss << _color.x << ' ' << _color.y << ' ' << _color.z << ' ';
            ss << _texPos.x << ' ' << _texPos.y;

            return ss.str();
        }
    };
}

#endif