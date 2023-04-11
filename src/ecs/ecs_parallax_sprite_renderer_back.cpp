#include "ecs_parallax_sprite_renderer_back.h"

omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::ECS_ParallaxSpriteRendererBack(const std::string& textureId, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack) : _sprite(textureId) , _layerOffsetCallBack(layerOffsetCallBack) {
    _layer = layer;

    _layerOffset = 0;

    ECS_ParallaxSpriteRendererBackSystem::get_instance().bind_component(this);

    ECS_ParallaxSpriteRendererBackSystem::get_instance().sort_components(
    [](const ECS_ParallaxSpriteRendererBack* a, const ECS_ParallaxSpriteRendererBack* b) {
        return a->get_layer() > b->get_layer();
    });
};

void omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::time_sync() {
    ECS_ParallaxSpriteRendererBackSystem::get_instance().bind_component(this);

    ECS_ParallaxSpriteRendererBackSystem::get_instance().sort_components(
    [](const ECS_ParallaxSpriteRendererBack* a, const ECS_ParallaxSpriteRendererBack* b) {
        return a->get_layer() > b->get_layer();
    });
}

u32 omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::render(const Shader *shader) {
    shader->set_uniform_f32("layerOffset", _layerOffsetCallBack(_layerOffset));
    _sprite.render(shader);
}
