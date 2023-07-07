#include "vertex.h"

omniscia::gfx::Vertex::Vertex(const Vec3f& pos, const Vec3f& color, const Vec2f& texPos) {
    _pos = pos;
    _color = color;
    _texPos = texPos;
}

void omniscia::gfx::Vertex::scale(const Vec3f& scale) {
    _pos.x *= scale.x;
    _pos.y *= scale.y;
    _pos.z *= scale.z;
}

void omniscia::gfx::Vertex::transform(const Vec3f& pos) {
    _pos += pos;
}

void omniscia::gfx::Vertex::rotate(const f32& angle) {
    auto mat = Matrix<f32, 2, 2>::get_rotation_matrix(angle);

    _pos.x = _pos.x * mat.e[0] - _pos.y * mat.e[1];
    _pos.y = _pos.x * mat.e[2] + _pos.y * mat.e[3];
}

std::string omniscia::gfx::Vertex::to_string() const {
    std::stringstream ss;

    ss << _pos.x << ' ' << _pos.y << ' ' << _pos.z << ' ';
    ss << _color.x << ' ' << _color.y << ' ' << _color.z << ' ';
    ss << _texPos.x << ' ' << _texPos.y;

    return ss.str();
}
