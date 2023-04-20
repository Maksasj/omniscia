#include "ecs_parallax_sprite_renderer_back.h"

omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::ECS_ParallaxSpriteRendererBack(const std::string& textureId, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack) : _sprite(textureId) , _layerOffsetCallBack(layerOffsetCallBack), ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("BackgroundStage")) {
    _layer = layer;

    _layerOffset = 0;

    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);
}

u32 omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::get_layer() const {
    return _layer;
}

void omniscia::core::ecs::ECS_ParallaxSpriteRendererBack::render() {
    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    shader->set_uniform_f32("layerOffset", _layerOffsetCallBack(_layerOffset));
    _sprite.render(shader);
}
