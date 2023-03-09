#include "sprite.h"

omniscia::renderer::sprite::Sprite::Sprite(const std::string& texture_id) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
    texture = TextureManager::get(texture_id).get_asset();
}

omniscia::renderer::sprite::Sprite::Sprite(const std::string& texture_id, const Vec3f& scale) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA, scale) {
    texture = TextureManager::get(texture_id).get_asset();
}

void omniscia::renderer::sprite::Sprite::set_texture_by_id(const std::string& texture_id) {
    texture = TextureManager::get(texture_id).get_asset();
}

void omniscia::renderer::sprite::Sprite::bind() {
    texture->bind();
    spriteMesh.bind();
}

void omniscia::renderer::sprite::Sprite::unbind() {
    omniscia::renderer::sprite::Sprite::texture->unbind();
    //spriteMesh.unbind();
}

omniscia::renderer::sprite::SpriteMesh& omniscia::renderer::sprite::Sprite::get_mesh() {
    return spriteMesh;
}

void omniscia::renderer::sprite::Sprite::draw() {
    bind(); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}
