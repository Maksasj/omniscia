#include "texture_buffer.h"

omniscia::gfx::texture::TextureBuffer::TextureBuffer() {

}

omniscia::gfx::texture::TextureBuffer::TextureBuffer(const u32& width, const u32& height) {
    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void omniscia::gfx::texture::TextureBuffer::bind() const {
    glBindTexture(GL_TEXTURE_2D, _ID);
}

void omniscia::gfx::texture::TextureBuffer::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
