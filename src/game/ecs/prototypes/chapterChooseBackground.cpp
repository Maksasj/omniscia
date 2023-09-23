#include "ecs/prototypes/chapterChooseBackground.h"

omniscia::core::ChapterChooseParallaxBackground::ChapterChooseParallaxBackground() : Entity() {
    add<ECS_ParallaxSpriteRendererBack>("chapter_choose_background_sky1_layer", 0, [](f32& layerOffset ) {
        layerOffset += Time::get_instance().get_delta_time();
        return (layerOffset / 300000.0f);
    });
    
    add<ECS_ParallaxSpriteRendererBack>("chapter_choose_background_sky2_layer", 1, [](f32& layerOffset) {
        layerOffset += Time::get_instance().get_delta_time();
        return -(layerOffset / 300000.0f);
    });

    add<ECS_ParallaxSpriteRendererBack>("chapter_choose_background_sky3_layer", 2, [](f32& layerOffset) {
        layerOffset += Time::get_instance().get_delta_time();
        return 2.0 * (layerOffset / 300000.0f);
    });
    
    add<ECS_ParallaxSpriteRendererBack>("chapter_choose_background_terrain_layer", 3, [](f32& layerOffset) { return 0.0f; });
}
