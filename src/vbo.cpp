#include "vbo.h"

omniscia::renderer::VBO::VBO(const std::vector<Vertex>& vertices) {
    glGenBuffers(1, &_ID);

    glBindBuffer(GL_ARRAY_BUFFER, _ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void omniscia::renderer::VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _ID);
}

void omniscia::renderer::VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void omniscia::renderer::VBO::terminate() const {
    glDeleteBuffers(1, &_ID);
}
