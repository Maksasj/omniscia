#include "ubo.h"

omniscia::gfx::UBO::UBO() {
    glGenBuffers(1, &_ID);

    glBindBuffer(GL_UNIFORM_BUFFER, _ID);
    glBufferData(GL_UNIFORM_BUFFER, UNIFORM_INSTANCING_DATA_SIZE * sizeof(InstancingData), nullptr, GL_DYNAMIC_DRAW);
}

void omniscia::gfx::UBO::bind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, _ID);
}

void omniscia::gfx::UBO::unbind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void omniscia::gfx::UBO::terminate() const {
    glDeleteBuffers(1, &_ID);
}
