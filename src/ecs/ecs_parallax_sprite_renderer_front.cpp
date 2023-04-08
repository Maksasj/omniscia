#include "ecs_parallax_sprite_renderer_front.h"

omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::ECS_ParallaxSpriteRendererFront(const std::string& texture_id, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack) : _sprite(texture_id) , _layerOffsetCallBack(layerOffsetCallBack) {
    _layer = layer;

    _layerOffset = 0;

    ECS_ParallaxSpriteRendererFrontSystem::get_instance().bind_component(this);

    ECS_ParallaxSpriteRendererFrontSystem::get_instance().sort_components(
    [](const ECS_ParallaxSpriteRendererFront* a, const ECS_ParallaxSpriteRendererFront* b) {
        return a->get_layer() > b->get_layer();
    });
};

void omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::time_sync() {
    ECS_ParallaxSpriteRendererFrontSystem::get_instance().bind_component(this);

    ECS_ParallaxSpriteRendererFrontSystem::get_instance().sort_components(
    [](const ECS_ParallaxSpriteRendererFront* a, const ECS_ParallaxSpriteRendererFront* b) {
        return a->get_layer() > b->get_layer();
    });
}

u32 omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::render(const Shader *shader) {
    shader->set_uniform_f32("layerOffset", _layerOffsetCallBack(_layerOffset));
    _sprite.render(shader);
}
