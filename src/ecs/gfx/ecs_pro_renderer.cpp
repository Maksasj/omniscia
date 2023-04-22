#include "ecs_pro_renderer.h"

omniscia::core::ecs::ECS_ProRenderer::ECS_ProRenderer(RenderStage* renderingStage) {
    _bindedRenderingStage = renderingStage;
};

omniscia::gfx::RenderStage* omniscia::core::ecs::ECS_ProRenderer::get_rendering_stage() const {
    return _bindedRenderingStage;
}
