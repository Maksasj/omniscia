#include "ecs_spritesheet_renderer.h"

omniscia::core::ecs::ECS_SpriteSheetRenderer::ECS_SpriteSheetRenderer(const std::string& texture_id, Entity& parent, const u32& layer) : _parent(parent) , _sprite(texture_id) {
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
    _parent = *(Entity*)parent;

    _animationIndex = _parent.get().index<ECS_SpriteAnimation>();
    _posIndex = _parent.get().index<ECS_Positioned>();
    _scaleIndex = _parent.get().index<ECS_Scaled>();
}

u32 omniscia::core::ecs::ECS_SpriteSheetRenderer::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_SpriteSheetRenderer::render(const Shader *shader) {
    Vec3f position = {0.0, 0.0, 0.0};
    Vec2f scale = {1.0, 1.0};
    Vec2f spriteFrameSize = {1.0, 1.0};
    Vec2f spriteFrameOffset = {0.0, 0.0};

    if(_posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent.get().ref_unsafe(_posIndex);

        position = positionComp.get_pos();
    }

    if(_scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent.get().ref_unsafe(_scaleIndex);

        scale = scaleComp.get_scale();
    }

    if(_animationIndex.is_success()) {
        ECS_SpriteAnimation &animationComp = _parent.get().ref_unsafe(_animationIndex);

        spriteFrameSize = animationComp.get_frame_size();
        spriteFrameOffset = animationComp.get_frame_offset();
    }

    _sprite.render(shader, position, 0.0f, scale, spriteFrameSize, spriteFrameOffset);
}
