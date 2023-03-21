#include "ebo.h"

omniscia::gfx::EBO::EBO(const std::vector<u32>& indices) {
    using namespace omniscia::core;
    
    glGenBuffers(1, &_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Vec3i), indices.data(), GL_STATIC_DRAW);
}

void omniscia::gfx::EBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void omniscia::gfx::EBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void omniscia::gfx::EBO::terminate() const {
    glDeleteBuffers(1, &_ID);
}
