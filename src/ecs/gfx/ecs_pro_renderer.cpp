#include "ecs_pro_renderer.h"

omniscia::core::ecs::ECS_ProRenderer::ECS_ProRenderer(RenderStage* renderingStage, const u32& layer) {
    _bindedRenderingStage = renderingStage;

    _layer = layer;
};

omniscia::gfx::RenderStage* omniscia::core::ecs::ECS_ProRenderer::get_rendering_stage() const {
    return _bindedRenderingStage;
}

omni::types::u32 omniscia::core::ecs::ECS_ProRenderer::get_layer() const {
    return _layer;
}
