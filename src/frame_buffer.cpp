#include "frame_buffer.h"

omniscia::renderer::FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

void omniscia::renderer::FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

void omniscia::renderer::FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void omniscia::renderer::FrameBuffer::terminate() const {

}

void omniscia::renderer::FrameBuffer::bind_target_texture_buffer(const omniscia::renderer::texture::TextureBuffer& textureBuffer) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureBuffer.get_id(), 0);
}
