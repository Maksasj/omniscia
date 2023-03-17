#include "sprite.h"

omniscia::renderer::sprite::Sprite::Sprite() : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
    texture = nullptr;
}

omniscia::renderer::sprite::Sprite::Sprite(const std::string& texture_id) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
    texture = TextureManager::get_instance().get(texture_id).get_asset();
}

omniscia::renderer::sprite::Sprite::Sprite(const std::string& texture_id, const Vec3f& scale) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA, scale) {
    texture = TextureManager::get_instance().get(texture_id).get_asset();
}

void omniscia::renderer::sprite::Sprite::set_texture_by_id(const std::string& texture_id) {
    texture = TextureManager::get_instance().get(texture_id).get_asset();
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

/*
void omniscia::renderer::sprite::Sprite::render() {
    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}
*/

void omniscia::renderer::sprite::Sprite::render(const Shader *shader) const {
    shader->set_uniform_vec2f("transform", Vec2f{0.0, 0.0});
    shader->set_uniform_f32("rotation", 0.0);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", 0.0);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const float &rotation) const {
    shader->set_uniform_vec2f("transform", Vec2f{0.0, 0.0});
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation) const { 
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    
    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const {    
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", 0.0);
    shader->set_uniform_vec2f("scale", scale);

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", scale);

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::renderer::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteFrameOffset) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", scale);

    shader->set_uniform_vec2f("spriteFrameSize", spriteFrameSize);
    shader->set_uniform_vec2f("spriteFrameOffset", spriteFrameOffset);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

