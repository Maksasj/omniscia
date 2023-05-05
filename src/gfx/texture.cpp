#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

omniscia::gfx::texture::Texture::Texture() {
    /*
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    i32 width, height, nrChannels;

    u8 *data = stbi_load("assets/texture.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    */
}

omni::types::u32 omniscia::gfx::texture::Texture::get_width() const {
    return _width;
}

omni::types::u32 omniscia::gfx::texture::Texture::get_height() const {
    return _height;
}

omni::types::f32 omniscia::gfx::texture::Texture::get_aspect() const {
    return _aspect;
}

omni::types::u32 omniscia::gfx::texture::Texture::get_color_channels() const {
    return _colorChannels;
}

void omniscia::gfx::texture::Texture::set_width(u32 width) {
    _width = width;
}

void omniscia::gfx::texture::Texture::set_height(u32 height) {
    _height = height;
}

void omniscia::gfx::texture::Texture::set_aspect(f32 aspect) {
    _aspect = aspect;
}

void omniscia::gfx::texture::Texture::set_color_channels(u32 colorChannels) {
    _colorChannels = colorChannels;
}
