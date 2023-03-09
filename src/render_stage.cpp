#include "render_stage.h"

omniscia::renderer::RenderStage::RenderStage() : FrameBuffer() {
    _textureBuffer = nullptr;
    _shader = nullptr;
}

void omniscia::renderer::RenderStage::present_as_texture() const {
    _textureBuffer->bind();
    _spriteMesh.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void omniscia::renderer::RenderStage::bind_target_mesh(const RawMeshData& rawMeshData) {
    _spriteMesh = SpriteMesh(rawMeshData);
}

void omniscia::renderer::RenderStage::bind_target_mesh(const RawMeshData& rawMeshData, const Vec3f scale) {
    _spriteMesh = SpriteMesh(rawMeshData, scale);
}

void omniscia::renderer::RenderStage::bind_target_texture_buffer(TextureBuffer *textureBuffer) {
    _textureBuffer = textureBuffer;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureBuffer->get_id(), 0);
}

void omniscia::renderer::RenderStage::bind_target_texture_buffer(TextureBuffer& textureBuffer) {
    _textureBuffer = &textureBuffer;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureBuffer->get_id(), 0);
}

void omniscia::renderer::RenderStage::bind_default_shader(Shader *shader) {
    _shader = shader;
}

void omniscia::renderer::RenderStage::bind_default_shader(Shader& shader) {
    _shader = &shader;
}

void omniscia::renderer::RenderStage::render_stage_lambda(const std::function<void(void)> rendering_lambda) const {        
    bind();
        if(_shader != nullptr)
            _shader->activate();

        rendering_lambda();
    
    unbind();
}

void omniscia::renderer::RenderStage::render_stage_lambda_default(const std::function<void(void)> rendering_lambda) const {
    bind();
        
        rendering_lambda();
    
    unbind();
}

void omniscia::renderer::RenderStage::render_anonymous_stage_lambda(const std::function<void(void)> rendering_lambda) {
    rendering_lambda();
}
