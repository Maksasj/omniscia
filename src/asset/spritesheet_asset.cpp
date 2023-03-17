#include "spritesheet_asset.h"

omniscia::core::SpriteAsset::SpriteAsset() {

}

omniscia::core::SpriteAsset::SpriteAsset(const std::string& file_path, u32 width, u32 height, u32 spriteWidth, u32 spriteHeight) : Asset(file_path) {
        u32 _width = width;
        u32 _height = height;
        u32 _spriteWidth = spriteWidth;
        u32 _spriteHeight = spriteHeight;
}

void omniscia::core::SpriteAsset::load_asset() {
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, _asset.get_id_ref());
    glBindTexture(GL_TEXTURE_2D, _asset.get_id());
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    i32 width, height, nrChannels;

    u8 *data = stbi_load(_file_path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);

    _asset.unbind();
}
