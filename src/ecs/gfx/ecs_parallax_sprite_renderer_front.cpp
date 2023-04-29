#include "ecs_parallax_sprite_renderer_front.h"

omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::ECS_ParallaxSpriteRendererFront(const std::string& texture_id, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack) : _sprite(texture_id) , _layerOffsetCallBack(layerOffsetCallBack), ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("IntermediateStage"), layer) {
    _layerOffset = 0;

    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::reindex(void* parent) {
    _parent = (Entity*)parent;

    _transparencyIndex = _parent->index<ECS_Transparency>();
}

void omniscia::core::ecs::ECS_ParallaxSpriteRendererFront::render() {
    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    shader->set_uniform_f32("layerOffset", _layerOffsetCallBack(_layerOffset));
    
    if(_transparencyIndex.is_success()) {
        ECS_Transparency& transparencyComp = _parent->ref_unsafe(_transparencyIndex);
        shader->set_uniform_f32("transparency", transparencyComp.get_transparency());
    }
    
    _sprite.render(shader);
    
    shader->set_uniform_f32("transparency", 1.0f);
}
