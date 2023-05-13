#include "ecs_gui_spritesheet_renderer.h"

omniscia::core::ecs::ECS_GuiSpriteSheetRenderer::ECS_GuiSpriteSheetRenderer(const std::string& textureId, const u32& layer) : _sprite(textureId), ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("GuiStage"), layer) {
    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_GuiSpriteSheetRenderer::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_GuiSpriteSheetRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
    _animationIndex = _parent->index<ECS_SpriteAnimation>();
    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
    _transparencyIndex = _parent->index<ECS_Transparency>();
}

void omniscia::core::ecs::ECS_GuiSpriteSheetRenderer::render() {
    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    Vec3f position = {0.0, 0.0, 0.0};
    Vec2f scale = {1.0, 1.0};
    Vec2f spriteFrameSize = {1.0, 1.0};
    Vec2f spriteFrameOffset = {0.0, 0.0};

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

    if(_transparencyIndex.is_success()) {
        ECS_Transparency& transparencyComp = _parent->ref_unsafe(_transparencyIndex);
        shader->set_uniform_f32("transparency", transparencyComp.get_transparency());
    }
    
    _sprite.render(shader, position, 0.0f, scale, spriteFrameSize, spriteFrameOffset, horizontalFlip, verticalFlip);
    
    shader->set_uniform_f32("transparency", 1.0f);
}
