#include "frame_buffer.h"

omniscia::gfx::FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

omniscia::gfx::FrameBuffer::~FrameBuffer() {

}

void omniscia::gfx::FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

void omniscia::gfx::FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void omniscia::gfx::FrameBuffer::bind_target_texture_buffer(const omniscia::gfx::texture::TextureBuffer& textureBuffer) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureBuffer.get_id(), 0);
}
