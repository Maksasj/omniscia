#include "ecs_tilemap_renderer.h"

omniscia::core::ecs::ECS_TilemapRenderer::ECS_TilemapRenderer(const RawMeshData& meshData, const std::string& texture_id, const u32& layer) : _sprite(meshData, texture_id) {
    _layer = layer;

    ECS_TilemapRendererSystem::get_instance().bind_component(this);

    ECS_TilemapRendererSystem::get_instance().sort_components(
    [](const ECS_TilemapRenderer* a, const ECS_TilemapRenderer* b) {
        return a->get_layer() > b->get_layer();
    });
};

void omniscia::core::ecs::ECS_TilemapRenderer::time_sync() {
    ECS_TilemapRendererSystem::get_instance().bind_component(this);

    ECS_TilemapRendererSystem::get_instance().sort_components(
    [](const ECS_TilemapRenderer* a, const ECS_TilemapRenderer* b) {
        return a->get_layer() > b->get_layer();
    });
}

void omniscia::core::ecs::ECS_TilemapRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
}

u32 omniscia::core::ecs::ECS_TilemapRenderer::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_TilemapRenderer::render(const Shader *shader) {
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

    if(_spriteFlipIndex.is_success()) {
        ECS_SpriteFlip &spriteFlipComp = _parent->ref_unsafe(_spriteFlipIndex);
        verticalFlip = spriteFlipComp.get_vertical_flip();
        horizontalFlip = spriteFlipComp.get_horizontal_flip();
    }

    _sprite.render(shader, position, 0.0f, scale, spriteFrameSize, spriteFrameOffset, horizontalFlip, verticalFlip);
}