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
