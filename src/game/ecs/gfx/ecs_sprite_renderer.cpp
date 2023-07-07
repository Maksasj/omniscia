#include "ecs_sprite_renderer.h"

omniscia::core::ecs::ECS_SpriteRenderer::ECS_SpriteRenderer(const std::string& textureId, const u32& layer) : _sprite(textureId), ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("MainStage"), layer) {
    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_SpriteRenderer::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_SpriteRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
    _transparencyIndex = _parent->index<ECS_Transparency>();
    _spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
}

void omniscia::core::ecs::ECS_SpriteRenderer::set_texture_by_id(const std::string& textureId) {
    _sprite.set_texture_by_id(textureId);
}

void omniscia::core::ecs::ECS_SpriteRenderer::render() {
    if(!_enabled) return;

    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    Vec3f position = Vec3f::splat(0.0f);
    Vec2f scale = Vec2f::splat(1.0f);

    bool horizontalSpriteFlip = false;
    bool verticalSpriteFlip = false;

    if(_posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent->ref_unsafe(_posIndex);

        position = positionComp.get_pos();
    }

    if(_scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent->ref_unsafe(_scaleIndex);

        scale = scaleComp.get_scale();
    }

    if(_transparencyIndex.is_success()) {
        ECS_Transparency& transparencyComp = _parent->ref_unsafe(_transparencyIndex);
        shader->set_uniform_f32("transparency", transparencyComp.get_transparency());
    }
    
    if(_spriteFlipIndex.is_success()) {
        ECS_SpriteFlip& spriteFlipComp = _parent->ref_unsafe(_spriteFlipIndex);

        horizontalSpriteFlip = spriteFlipComp.get_horizontal_flip();
        verticalSpriteFlip = spriteFlipComp.get_vertical_flip();
    }

    _sprite.render(shader, position, scale, horizontalSpriteFlip, verticalSpriteFlip);
    
    shader->set_uniform_f32("transparency", 1.0f);
}
