#include "ecs_popup_renderer.h"

omniscia::core::ecs::ECS_PopupRenderer::ECS_PopupRenderer(const std::string& textureId, const u32& layer, const std::string& popupAnimation) 
        :   _sprite(textureId), 
            _animationComp(popupAnimation),
            ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("MainStage"), layer) {
                
    _offset = Vec2f{0.0f, 0.0f};

    _scale = 1.0f;
   
    ECS_ProRendererSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PopupRenderer::time_sync() {
    ECS_ProRendererSystem::get_instance().bind_component(this);

    _animationComp.time_sync();
}

void omniscia::core::ecs::ECS_PopupRenderer::reindex(void* parent) {
    _parent = (Entity*)parent;

    _animationComp.reindex(parent);

    _posIndex = _parent->index<ECS_Positioned>();
}

void omniscia::core::ecs::ECS_PopupRenderer::render() {
    if(!_enabled) return;

    Shader* shader = Shader::get_active();
    if(shader == nullptr)
        return;

    if(!is_enabled())
        return;

    Vec3f position = {0.0, 0.0, 0.0};
    Vec2f scale = {_scale, _scale};
    Vec2f spriteFrameSize = {1.0, 1.0};
    Vec2f spriteFrameOffset = {0.0, 0.0};

    bool verticalFlip = false;
    bool horizontalFlip = false;

    if(_posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent->ref_unsafe(_posIndex);

        position = positionComp.get_pos();
    }

    spriteFrameSize = _animationComp.get_frame_size();
    spriteFrameOffset = _animationComp.get_frame_offset();

    position.x += _offset.x;
    position.y += _offset.y;

    shader->set_uniform_f32("transparency", _transparency);
    _sprite.render(shader, position, 0.0f, scale, spriteFrameSize, spriteFrameOffset, horizontalFlip, verticalFlip);
    shader->set_uniform_f32("transparency", 1.0f);
}