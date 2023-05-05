#include "texture_asset.h"

omni::types::u32 omniscia::core::TextureAsset::_count = 0;


omniscia::core::TextureAsset::TextureAsset() { ++_count; }

omniscia::core::TextureAsset::TextureAsset(const std::string& filePath) : Asset(filePath) { ++_count; }

void omniscia::core::TextureAsset::load_asset() {
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, _asset.get_id_ref());
    glBindTexture(GL_TEXTURE_2D, _asset.get_id());
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    i32 width, height, nrChannels;

    u8 *data = stbi_load(_filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        _asset.set_width(width);
        _asset.set_height(height);
        _asset.set_aspect((f32)width / (f32)height);
        _asset.set_color_channels(nrChannels);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);

    _asset.unbind();
}

omni::types::u32 omniscia::core::TextureAsset::get_count() {
    return _count;
}
