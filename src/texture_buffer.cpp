#include "texture_buffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

omniscia::renderer::texture::TextureBuffer::TextureBuffer() {
    
}

omniscia::renderer::texture::TextureBuffer::TextureBuffer(const u32& width, const u32& height) {
    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void omniscia::renderer::texture::TextureBuffer::bind()  {
    glBindTexture(GL_TEXTURE_2D, _ID);
}

void omniscia::renderer::texture::TextureBuffer::unbind()  {
    glBindTexture(GL_TEXTURE_2D, 0);
}
