#include "instancing_sprite.h"

omniscia::gfx::sprite::InstancingSprite::InstancingSprite(const std::string& textureId) : _spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
    _texture = TextureManager::get_instance().get(textureId).get_asset();
}

omniscia::gfx::sprite::InstancingSprite::InstancingSprite(const RawMeshData& spriteMesh, const std::string& textureId) : _spriteMesh(spriteMesh) {
    _texture = TextureManager::get_instance().get(textureId).get_asset();
}

void omniscia::gfx::sprite::InstancingSprite::set_texture_by_id(const std::string& textureId) {
    _texture = TextureManager::get_instance().get(textureId).get_asset();
}

void omniscia::gfx::sprite::InstancingSprite::bind() const {
    _texture->bind();
    _spriteMesh.bind();
}

void omniscia::gfx::sprite::InstancingSprite::unbind() const {
    omniscia::gfx::sprite::InstancingSprite::_texture->unbind();
}

omniscia::gfx::sprite::SpriteMesh& omniscia::gfx::sprite::InstancingSprite::get_mesh() {
    return _spriteMesh;
}

void omniscia::gfx::sprite::InstancingSprite::render(const Shader *shader, const std::vector<InstancingData>& instancingData, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset, const bool& horizontalFlip, const bool& verticalFlip) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_rotation_matrix(rotationAngle));

    shader->set_uniform_vec2f("spriteFrameSize", spriteFrameSize);
    shader->set_uniform_vec2f("spriteFrameOffset", spriteSheetOffset);

    shader->set_uniform_i32("textureFlipHorizontal", horizontalFlip);
    shader->set_uniform_i32("textureFlipVertical", verticalFlip);

    shader->set_uniform_f32("textureAspect", _texture->get_aspect());

    _ubo.bind();

    shader->bind_ubo("InstancingData", _ubo);

    InstancingData* instances = _ubo.open();

    if(instances == nullptr) return;

    const i32 actualInstanceCount = instancingData.size();
    const i32 clampedInstanceCount = UNIFORM_INSTANCING_DATA_SIZE < actualInstanceCount ? UNIFORM_INSTANCING_DATA_SIZE : actualInstanceCount; 

    for(int i = 0; i < clampedInstanceCount; ++i) {
        instances[i]._position = instancingData[i]._position;
        instances[i]._scale = instancingData[i]._scale;
        instances[i]._frameSize = instancingData[i]._frameSize;
        instances[i]._frameOffset = instancingData[i]._frameOffset;
    }

    _ubo.close();
    
    shader->set_uniform_i32("isInstancing", 1);

    bind(); 
        glDrawElementsInstanced(GL_TRIANGLES, _spriteMesh.get_indices_count(), GL_UNSIGNED_INT, 0, clampedInstanceCount);
    unbind();

    shader->set_uniform_i32("isInstancing", 0);
}

omni::types::u64 omniscia::gfx::sprite::InstancingSprite::byte_size() const { 
    return sizeof(Texture*) + _spriteMesh.byte_size();
}
