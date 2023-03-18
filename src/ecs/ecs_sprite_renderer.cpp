#include "ecs_sprite_renderer.h"

omniscia::core::ecs::ECS_SpriteRenderer::ECS_SpriteRenderer(const std::string& texture_id, Entity& parent, const u32& layer) : _parent(parent) , _sprite(texture_id) {
    _layer = layer;

    ECS_SpriteRendererSystem::get_instance().bind_component(this);

    ECS_SpriteRendererSystem::get_instance().sort_components(
    [](const ECS_SpriteRenderer* a, const ECS_SpriteRenderer* b) {
        return a->get_layer() > b->get_layer();
    });
};

void omniscia::core::ecs::ECS_SpriteRenderer::time_sync() {
    ECS_SpriteRendererSystem::get_instance().bind_component(this);

    ECS_SpriteRendererSystem::get_instance().sort_components(
    [](const ECS_SpriteRenderer* a, const ECS_SpriteRenderer* b) {
        return a->get_layer() > b->get_layer();
    });
}


void omniscia::core::ecs::ECS_SpriteRenderer::reindex(void* parent) {
    _parent = *(Entity*)parent;

    _posIndex = _parent.get().index<ECS_Positioned>();
    _scaleIndex = _parent.get().index<ECS_Scaled>();
}

u32 omniscia::core::ecs::ECS_SpriteRenderer::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_SpriteRenderer::render(const Shader *shader) {
    Vec3f position = {0.0, 0.0, 0.0};
    Vec2f scale = {1.0, 1.0};

    if(_posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent.get().ref_unsafe(_posIndex);

        position = positionComp.get_pos();
    }

    if(_scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent.get().ref_unsafe(_scaleIndex);

        scale = scaleComp.get_scale();
    }

    _sprite.render(shader, position, scale);
}
