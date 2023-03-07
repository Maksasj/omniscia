#include "vao.h"

omniscia::renderer::VAO::VAO() {
    glGenVertexArrays(1, &_ID);
}

void omniscia::renderer::VAO::link_attribute(u32 index, u32 componentsNumber, u32 type, u32 strideSize, void* offset) {
    glVertexAttribPointer(index, componentsNumber, type, GL_FALSE, strideSize, offset);
    glEnableVertexAttribArray(index);
}

void omniscia::renderer::VAO::bind() {
    glBindVertexArray(_ID);
}

void omniscia::renderer::VAO::unbind() {
    glBindVertexArray(0);
}

void omniscia::renderer::VAO::terminate() {
    glDeleteVertexArrays(1, &_ID);
}
