#include "ecs_sprite_renderer.h"

omniscia::core::ecs::ECS_SpriteRenderer::ECS_SpriteRenderer(const std::string& texture_id, Entity& parent) : _parent(parent) , _sprite(texture_id) {
    ECS_SpriteRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_SpriteRenderer::time_sync() {
    ECS_SpriteRendererSystem::get_instance().bind_component(this);
}
