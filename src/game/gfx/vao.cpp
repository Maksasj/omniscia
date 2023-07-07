#include "vao.h"

omniscia::gfx::VAO::VAO() {
    glGenVertexArrays(1, &_ID);
}

omniscia::gfx::VAO::~VAO() {
    glGenVertexArrays(1, &_ID);
}


void omniscia::gfx::VAO::link_attribute(u32 index, u32 componentsNumber, u32 type, u32 strideSize, void* offset) {
    glVertexAttribPointer(index, componentsNumber, type, GL_FALSE, strideSize, offset);
    glEnableVertexAttribArray(index);
}

void omniscia::gfx::VAO::bind() const {
    glBindVertexArray(_ID);
}

void omniscia::gfx::VAO::unbind() const {
    glBindVertexArray(0);
}

void omniscia::gfx::VAO::terminate() const {
    glDeleteVertexArrays(1, &_ID);
}
