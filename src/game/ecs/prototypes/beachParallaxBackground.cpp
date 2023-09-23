#include "ecs/prototypes/beachParallaxBackground.h"

omniscia::core::BeachParallaxBackground::BeachParallaxBackground() : Entity() {
    add<ECS_ParallaxSpriteRendererBack>("background_beach_sky1_layer", 0, [](f32& layerOffset ) {
        layerOffset += Time::get_instance().get_delta_time();
        return (layerOffset / 100000.0f);
    });
    
    add<ECS_ParallaxSpriteRendererBack>("background_beach_sky2_layer", 1, [](f32& layerOffset) {
        layerOffset += Time::get_instance().get_delta_time();
        return 2.0f * (layerOffset / 100000.0f);
    });

    add<ECS_ParallaxSpriteRendererBack>("background_beach_beach_layer", 2, [](f32& layerOffset) {
        layerOffset = DebugInfo::get_instance().get_metrics()._playerPos.x;
        return (layerOffset / 500.0f) * 10.5f;
    });
    
    add<ECS_ParallaxSpriteRendererBack>("background_beach_terrain_layer", 3, [](f32& layerOffset) {
        layerOffset = DebugInfo::get_instance().get_metrics()._playerPos.x;
        return (layerOffset / 500.0f) * 21.0f;
    });

    add<ECS_ParallaxSpriteRendererFront>("background_beach_grass_overlay_layer", 0, [](f32& layerOffset) {
        layerOffset = DebugInfo::get_instance().get_metrics()._playerPos.x;
        return (layerOffset / 500.0f) * 100.0f;
    });
}
