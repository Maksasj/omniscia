#include "render_stage.h"

omniscia::gfx::RenderStage* omniscia::gfx::RenderStage::_activeRenderStage = nullptr;

omniscia::gfx::RenderStage::RenderStage(const i32& stageId) : FrameBuffer() {
    _stageId = stageId;

    _textureBuffer = nullptr;
    _defaultShader = nullptr;

    _clearBufferColor = Vec4f::splat(0.0f);
    _uniformLambda = [](const Shader*) {};
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

    _textureBuffer->unbind();
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position, const float &rotation) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    _textureBuffer->unbind();
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position, const Vec2f &scale) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_vec2f("scale", scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    _textureBuffer->unbind();
}

void omniscia::gfx::RenderStage::present_as_texture(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const {
    _textureBuffer->bind();
    _spriteMesh.bind();

    shader->set_uniform_vec2f("transform", position);
    shader->set_uniform_f32("rotation", rotation);
    shader->set_uniform_vec2f("scale", scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    _textureBuffer->unbind();
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_target_mesh(const SpriteMesh& spriteMesh) {
    _spriteMesh = spriteMesh;
    
    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_target_texture_buffer(TextureBuffer *textureBuffer) {
    _textureBuffer = textureBuffer;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureBuffer->get_id(), 0);
    unbind();

    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_target_texture_buffer(TextureBuffer& textureBuffer) {
    _textureBuffer = &textureBuffer;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureBuffer->get_id(), 0);
    unbind();
    
    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_default_shader(Shader *shader) {
    _defaultShader = shader;

    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_default_shader(Shader& shader) {
    _defaultShader = &shader;

    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_shader_uniform(const std::function<void(const Shader* shader)>& uniformLambda) {
    _uniformLambda = uniformLambda;

    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_default_buffer_clear(const Vec4f& color) {
    _clearBufferColor = color;

    return *this;
}

omniscia::gfx::RenderStage& omniscia::gfx::RenderStage::bind_viewport_size(const Vec4f& viewPort) {
    _viewPort = viewPort;

    return *this;
}

void omniscia::gfx::RenderStage::render_stage_lambda(const std::function<void(void)>& renderingLambda) {        
    bind();
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        glViewport(_viewPort.x, _viewPort.y, _viewPort.z, _viewPort.w);

        _activeRenderStage = this;

        Renderer::clear_buffer(_clearBufferColor);

        if(_defaultShader != nullptr)
            _defaultShader->activate();

        Shader* activeShader = Shader::get_active();

        _uniformLambda(activeShader);

        renderingLambda();

        _activeRenderStage = nullptr;
    unbind();
}

void omniscia::gfx::RenderStage::render_stage_lambda(const std::function<void(const Shader* shader)>& renderingLambda) {        
    bind();
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        glViewport(_viewPort.x, _viewPort.y, _viewPort.z, _viewPort.w);

        _activeRenderStage = this;

        Renderer::clear_buffer(_clearBufferColor);

        if(_defaultShader != nullptr)
            _defaultShader->activate();

        Shader* activeShader = Shader::get_active();

        _uniformLambda(activeShader);

        renderingLambda(activeShader);

        _activeRenderStage = nullptr;
    unbind();
}

void omniscia::gfx::RenderStage::render_stage_lambda_default(const std::function<void(void)>& renderingLambda) {
    bind();
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        _activeRenderStage = this;
        
        renderingLambda();

        _activeRenderStage = nullptr;
    unbind();
}

void omniscia::gfx::RenderStage::render_anonymous_stage_lambda(const std::function<void(void)>& renderingLambda) {
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
   
    _activeRenderStage = nullptr;
    
    renderingLambda();
    
    _activeRenderStage = nullptr;
}

omniscia::gfx::RenderStage* omniscia::gfx::RenderStage::get_active_render_stage() {
    return _activeRenderStage;
}

omni::types::i32 omniscia::gfx::RenderStage::get_stage_id() const {
    return _stageId;
} 
