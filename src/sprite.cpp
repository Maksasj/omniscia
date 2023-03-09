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

void omniscia::renderer::sprite::Sprite::bind() const {
    texture->bind();
    spriteMesh.bind();
}

void omniscia::renderer::sprite::Sprite::unbind() const {
    omniscia::renderer::sprite::Sprite::texture->unbind();
    //spriteMesh.unbind();
}

omniscia::renderer::sprite::SpriteMesh& omniscia::renderer::sprite::Sprite::get_mesh() {
    return spriteMesh;
}

void omniscia::renderer::sprite::Sprite::render() {
    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position) const {
    shader->set_uniform_vec2f("transform", position);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const float &rotation) const {
    shader->set_uniform_f32("rotation", rotation);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    
    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", scale);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}
