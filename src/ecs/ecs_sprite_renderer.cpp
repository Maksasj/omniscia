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
