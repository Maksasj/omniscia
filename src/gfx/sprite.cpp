#include "sprite.h"

omniscia::gfx::sprite::Sprite::Sprite() : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
    texture = nullptr;
}

omniscia::gfx::sprite::Sprite::Sprite(const std::string& texture_id) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
    texture = TextureManager::get_instance().get(texture_id).get_asset();
}

omniscia::gfx::sprite::Sprite::Sprite(const std::string& texture_id, const Vec3f& scale) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA, scale) {
    texture = TextureManager::get_instance().get(texture_id).get_asset();
}

void omniscia::gfx::sprite::Sprite::set_texture_by_id(const std::string& texture_id) {
    texture = TextureManager::get_instance().get(texture_id).get_asset();
}

void omniscia::gfx::sprite::Sprite::bind() const {
    texture->bind();
    spriteMesh.bind();
}

void omniscia::gfx::sprite::Sprite::unbind() const {
    omniscia::gfx::sprite::Sprite::texture->unbind();
    //spriteMesh.unbind();
}

omniscia::gfx::sprite::SpriteMesh& omniscia::gfx::sprite::Sprite::get_mesh() {
    return spriteMesh;
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader) const {
    shader->set_uniform_vec2f("transform", Vec2f{0.0, 0.0});
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_zero_rotation_matrix());

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});
    
    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_zero_rotation_matrix());

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const float &rotationAngle) const {
    shader->set_uniform_vec2f("transform", Vec2f{0.0, 0.0});
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_rotation_matrix(rotationAngle));

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const {    
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_zero_rotation_matrix());

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotationAngle) const { 
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_rotation_matrix(rotationAngle));
    
    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_f32("rotation", rotation);

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteFrameOffset) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_rotation_matrix(rotation));

    shader->set_uniform_vec2f("spriteFrameSize", spriteFrameSize);
    shader->set_uniform_vec2f("spriteFrameOffset", spriteFrameOffset);

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Matrix<f32, 2, 2> &rotation) const {
    shader->set_uniform_vec2f("transform", Vec2f{0.0, 0.0});
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    shader->set_uniform_mat2x2f("rotation", rotation);

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation) const { 
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", Vec2f{1.0, 1.0});
    shader->set_uniform_mat2x2f("rotation", rotation);
    
    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation, const Vec2f &scale) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_mat2x2f("rotation", rotation);

    shader->set_uniform_vec2f("spriteFrameSize", Vec2f{1.0, 1.0});
    shader->set_uniform_vec2f("spriteFrameOffset", Vec2f{0.0, 0.0});

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2u, 2u> &rotation, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteFrameOffset) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_mat2x2f("rotation", rotation);

    shader->set_uniform_vec2f("spriteFrameSize", spriteFrameSize);
    shader->set_uniform_vec2f("spriteFrameOffset", spriteFrameOffset);

    shader->set_uniform_i32("textureFlipHorizontal", false);
    shader->set_uniform_i32("textureFlipVertical", false);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}

void omniscia::gfx::sprite::Sprite::render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset, const bool& horizontalFlip, const bool& verticalFlip) const {
    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);
    shader->set_uniform_mat2x2f("rotation", Matrix<f32, 2, 2>::get_rotation_matrix(rotationAngle));

    shader->set_uniform_vec2f("spriteFrameSize", spriteFrameSize);
    shader->set_uniform_vec2f("spriteFrameOffset", spriteSheetOffset);

    shader->set_uniform_i32("textureFlipHorizontal", horizontalFlip);
    shader->set_uniform_i32("textureFlipVertical", verticalFlip);

    bind(); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbind();
}