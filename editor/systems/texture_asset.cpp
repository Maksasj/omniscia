#include "texture_asset.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool omniscia_editor::systems::TextureAsset::load_asset_from_file() {
    i32 image_width = 0;
    i32 image_height = 0;
    u8* image_data = stbi_load(_filePath.c_str(), &image_width, &image_height, NULL, 4);
    
    if (image_data == NULL)
        return false;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    _texture = image_texture;
    _width = image_width;
    _height = image_height;

    return true;
}
