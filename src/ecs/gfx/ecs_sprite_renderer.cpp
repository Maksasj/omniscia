#include "ecs_sprite_renderer.h"

omniscia::core::ecs::ECS_SpriteRenderer::ECS_SpriteRenderer(const std::string& textureId, const u32& layer) : _sprite(textureId), ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("MainStage")) {
    _layer = layer;

    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_SpriteRenderer::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_SpriteRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
}

u32 omniscia::core::ecs::ECS_SpriteRenderer::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_SpriteRenderer::render() {
    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    Vec3f position = {0.0, 0.0, 0.0};
    Vec2f scale = {1.0, 1.0};

    if(_posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent->ref_unsafe(_posIndex);

        position = positionComp.get_pos();
    }

    if(_scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent->ref_unsafe(_scaleIndex);

        scale = scaleComp.get_scale();
    }

    _sprite.render(shader, position, scale);
}
