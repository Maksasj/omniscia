#include "ecs_spritesheet_renderer.h"

omniscia::core::ecs::ECS_SpriteSheetRenderer::ECS_SpriteSheetRenderer(const std::string& textureId, const u32& layer) : _sprite(textureId) {
    _layer = layer;

    ECS_SpriteSheetRendererSystem::get_instance().bind_component(this);

    ECS_SpriteSheetRendererSystem::get_instance().sort_components(
    [](const ECS_SpriteSheetRenderer* a, const ECS_SpriteSheetRenderer* b) {
        return a->get_layer() > b->get_layer();
    });
};

void omniscia::core::ecs::ECS_SpriteSheetRenderer::time_sync() {
    ECS_SpriteSheetRendererSystem::get_instance().bind_component(this);

    ECS_SpriteSheetRendererSystem::get_instance().sort_components(
    [](const ECS_SpriteSheetRenderer* a, const ECS_SpriteSheetRenderer* b) {
        return a->get_layer() > b->get_layer();
    });
}

void omniscia::core::ecs::ECS_SpriteSheetRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
    _animationIndex = _parent->index<ECS_SpriteAnimation>();
    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
}

u32 omniscia::core::ecs::ECS_SpriteSheetRenderer::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_SpriteSheetRenderer::render(const Shader *shader) {
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

    _sprite.render(shader, position, 0.0f, scale, spriteFrameSize, spriteFrameOffset, horizontalFlip, verticalFlip);
}
