#include "ebo.h"

omniscia::renderer::EBO::EBO(const std::vector<u32>& indices) {
    using namespace omniscia::core;
    
    glGenBuffers(1, &_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Vec3i), indices.data(), GL_STATIC_DRAW);
}

void omniscia::renderer::EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void omniscia::renderer::EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void omniscia::renderer::EBO::terminate() {
    glDeleteBuffers(1, &_ID);
}