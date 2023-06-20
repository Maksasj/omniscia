#include "ecs_instancing_renderer.h"

omniscia::core::ecs::ECS_InstancingRenderer::ECS_InstancingRenderer(const std::string& textureId, const u32& layer) : _instancingSprite(textureId), ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("GuiStage"), layer) {
    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_InstancingRenderer::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_InstancingRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
    _animationIndex = _parent->index<ECS_SpriteAnimation>();
    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
}

void omniscia::core::ecs::ECS_InstancingRenderer::render() {
    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    Vec3f position = Vec3f::splat(0.0f);
    Vec2f scale = Vec2f::splat(1.0f);
    Vec2f spriteFrameSize = Vec2f::splat(1.0f);
    Vec2f spriteFrameOffset = Vec2f::splat(0.0f);

    bool verticalFlip = false;
    bool horizontalFlip = false;

    if(_posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent->ref_unsafe(_posIndex);

        position = positionComp.get_pos();
    }

    if(_scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent->ref_unsafe(_scaleIndex);

        scale = scaleComp.get_scale();
    }

    if(_animationIndex.is_success()) {
        ECS_SpriteAnimation &animationComp = _parent->ref_unsafe(_animationIndex);

        spriteFrameSize = animationComp.get_frame_size();
        spriteFrameOffset = animationComp.get_frame_offset();
    }

    if(_spriteFlipIndex.is_success()) {
        ECS_SpriteFlip &spriteFlipComp = _parent->ref_unsafe(_spriteFlipIndex);
        verticalFlip = spriteFlipComp.get_vertical_flip();
        horizontalFlip = spriteFlipComp.get_horizontal_flip();
    }

    _instancingSprite.render(
        shader, 
        _instancingData,
        position, 
        0.0f, scale, 
        spriteFrameSize, spriteFrameOffset, 
        horizontalFlip, verticalFlip
    );
}
