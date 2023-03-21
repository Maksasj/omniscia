#include "render_stage.h"

omniscia::gfx::RenderStage::RenderStage() : FrameBuffer() {
    _textureBuffer = nullptr;
    _shader = nullptr;
}

void omniscia::gfx::RenderStage::present_as_texture() const {
    _textureBuffer->bind();
    _spriteMesh.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const float &rotation) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_f32("rotation", rotation);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position, const float &rotation) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position, const Vec2f &scale) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::gfx::RenderStage::bind_target_mesh(const RawMeshData& rawMeshData) {
    _spriteMesh = SpriteMesh(rawMeshData);
}

void omniscia::gfx::RenderStage::bind_target_mesh(const RawMeshData& rawMeshData, const Vec3f scale) {
    _spriteMesh = SpriteMesh(rawMeshData, scale);
}

void omniscia::gfx::RenderStage::bind_target_texture_buffer(TextureBuffer *textureBuffer) {
    _textureBuffer = textureBuffer;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureBuffer->get_id(), 0);
}

void omniscia::gfx::RenderStage::bind_target_texture_buffer(TextureBuffer& textureBuffer) {
    _textureBuffer = &textureBuffer;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureBuffer->get_id(), 0);
}

void omniscia::gfx::RenderStage::bind_default_shader(Shader *shader) {
    _shader = shader;
}

void omniscia::gfx::RenderStage::bind_default_shader(Shader& shader) {
    _shader = &shader;
}

void omniscia::gfx::RenderStage::render_stage_lambda(const std::function<void(void)> rendering_lambda) const {        
    bind();
        if(_shader != nullptr)
            _shader->activate();

        rendering_lambda();
    
    unbind();
}

void omniscia::gfx::RenderStage::render_stage_lambda(const std::function<void(const Shader* shader)> rendering_lambda) const {        
    bind();
        if(_shader != nullptr)
            _shader->activate();

        rendering_lambda(_shader);
    unbind();
}

void omniscia::gfx::RenderStage::render_stage_lambda_default(const std::function<void(void)> rendering_lambda) const {
    bind();
        
        rendering_lambda();
    
    unbind();
}

void omniscia::gfx::RenderStage::render_anonymous_stage_lambda(const std::function<void(void)> rendering_lambda) {
    rendering_lambda();
}
