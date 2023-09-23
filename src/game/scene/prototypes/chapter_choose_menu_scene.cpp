#include "scene/prototypes/chapter_choose_menu_scene.h"
#include "game.h"

omniscia::core::ChapterChooseMenuScene::ChapterChooseMenuScene() : Scene() {
    add_static_entity<AnimatedButton>((AnimatedButtonProp) {
        ._pos = Vec2f{-1.07f, 0.15f},
        ._scale = Vec2f{0.1f, 0.1f},
        ._renderer = {
            ._texture = "chapter_buttons",
            ._animation = "chapter_1_unlocked_animation",
            ._layer = 1,
        },

        ._clickLambda = [](ECS_Button&) {
            Game::get_instance().start_cutscene("transition_cutscene_to_game_scene");
        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.105f, 0.105f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        }
    });
   
    add_static_entity<AnimatedButton>((AnimatedButtonProp) {
        ._pos = Vec2f{-1.07f, -0.07f},
        ._scale = Vec2f{0.1f, 0.1f},
        ._renderer = {
            ._texture = "chapter_buttons",
            ._animation = "chapter_2_locked_animation",
            ._layer = 1,
        },

        ._clickLambda = [](ECS_Button&) {

        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        }
    });

    add_static_entity<AnimatedButton>((AnimatedButtonProp) {
        ._pos = Vec2f{-1.07f, -0.29f},
        ._scale = Vec2f{0.1f, 0.1f},
        ._renderer = {
            ._texture = "chapter_buttons",
            ._animation = "chapter_3_locked_animation",
            ._layer = 1,
        },

        ._clickLambda = [](ECS_Button&) {

        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        }
    });

    add_static_entity<AnimatedButton>((AnimatedButtonProp) {
        ._pos = Vec2f{-1.07f, -0.51f},
        ._scale = Vec2f{0.1f, 0.1f},
        ._renderer = {
            ._texture = "chapter_buttons",
            ._animation = "chapter_4_locked_animation",
            ._layer = 1,
        },

        ._clickLambda = [](ECS_Button&) {

        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.1f, 0.1f});
        }
    });

    add_static_entity<AnimatedImage>((AnimatedImageProp) {
        ._texture = "logo_green_spritesheet",
        ._animation = "logo-animation",
        ._pos = Vec2f{-1.0f, 0.6f},
        ._scale = Vec2f{0.25f, 0.25f},
    });

    add_static_entity<AnimatedImage>((AnimatedImageProp) {
        ._texture = "selector_spritesheet",
        ._animation = "selector-animation",
        ._pos = Vec2f{-0.6f, 0.15f},
        ._scale = Vec2f{0.12f, 0.12f},
    });
    
    add_static_entity<Image>((ImageProp) {
        ._texture = "choose_panel",
        ._layer = 10, 
        ._pos = Vec2f{0.7f, 0.0f},
        ._scale = Vec2f{0.85f, 0.85f},
    });

    add_static_entity<AnimatedImage>((AnimatedImageProp) {
        ._texture = "chapter_1_thumbnail_spritesheet",
        ._animation = "chapter-1-thumbnail-animation",
        ._layer = 1,
        ._pos = Vec2f{0.7f, 0.35f},
        ._scale = Vec2f{0.3f, 0.3f},
    });

    add_static_entity<StaticText>(Vec2f{0.7f, -0.3f}, Vec2f{0.0375f, 0.0375f}, (StaticTextProp) {
        ._fontId = "monogram-gray",
        ._textToRender = "Embodied with malevolent enchantments, the cursed spikes pose a grave threat to anyone who comes into contact with them, as they have the power to disrupt both space and time. Your agility, quick reflexes, and strategic thinking will be crucial as you navigate through the intricate pathways, carefully evading the spikes to reach the Pink Crystal and restore harmony to the shattered timeline.",
        ._lineLetterSpacing = 0.31f,
        ._rowLineSpacing = 0.8f,
        ._charactersPerRow = 38u,
    });

    add_static_entity<ChapterChooseParallaxBackground>();
    //add_static_entity<MainMenuParallaxBackground>();

    unbind();
}
