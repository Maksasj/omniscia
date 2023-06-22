#include "main_menu_scene.h"
#include "game.h"

omniscia::core::MainMenuScene::MainMenuScene() : Scene() {
    // add_static_entity<StaticText>(Vec2f{0.0f, 0.8f}, Vec2f{0.03f, 0.03f}, (StaticTextProp) {
    //     ._fontId = "abaddon-light-white",
    //     ._textToRender = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.",
    //     ._lineLetterSpacing = 0.42f,
    //     ._rowLineSpacing = 0.8f,
    //     ._charactersPerRow = 24u,
    // });
// 
    // add_static_entity<StaticText>(Vec2f{-1.0f, 0.8f}, Vec2f{0.015f, 0.015f}, (StaticTextProp) {
    //     ._fontId = "abaddon-light-white",
    //     ._textToRender = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.",
    //     ._lineLetterSpacing = 0.42f,
    //     ._rowLineSpacing = 0.8f,
    //     ._charactersPerRow = 24u,
    // });
    
    add_static_entity<Button>((ButtonProp) {
        ._pos = Vec2f{-1.3f, 0.1f},
        ._scale = Vec2f{0.06f, 0.06f},
        ._renderer = {
            ._texture = "continue_button",
            ._layer = 1,
        },

        ._clickLambda = [](ECS_Button&) {
            Game::get_instance().start_cutscene("transition_cutscene_to_chapter_choose_scene");
        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.065f, 0.065f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.06f, 0.06f});
        }
    });

    add_static_entity<Button>((ButtonProp) {
        ._pos = Vec2f{-1.3f, 0.0f},
        ._scale = Vec2f{0.06f, 0.06f},
        ._renderer = {
            ._texture = "new_game_button",
            ._layer = 1,
        },
        
        ._clickLambda = [](ECS_Button&) {
            Game::get_instance().start_cutscene("transition_cutscene_to_chapter_choose_scene");
        },
        
        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.065f, 0.065f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.06f, 0.06f});
        }
    });

    add_static_entity<Button>((ButtonProp) {
        ._pos = Vec2f{-1.3f, -0.1f},
        ._scale = Vec2f{0.06f, 0.06f},
        ._renderer = {
            ._texture = "secrets_button",
            ._layer = 1,
        },
        
        ._clickLambda = [](ECS_Button&) {
            Game::get_instance().start_cutscene("transition_cutscene_to_secrets");
        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.065f, 0.065f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.06f, 0.06f});
        }
    });

    add_static_entity<Button>((ButtonProp) {
        ._pos = Vec2f{-1.3f, -0.2f},
        ._scale = Vec2f{0.06f, 0.06f},
        ._renderer = {
            ._texture = "options_button",
            ._layer = 1,
        },
        
        ._clickLambda = [](ECS_Button&) {
            Game::get_instance().start_cutscene("transition_cutscene_to_settings");
        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.065f, 0.065f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.06f, 0.06f});
        }
    });

    add_static_entity<Button>((ButtonProp) {
        ._pos = Vec2f{-1.3f, -0.3f},
        ._scale = Vec2f{0.06f, 0.06f},
        ._renderer = {
            ._texture = "quit_game_button",
            ._layer = 1,
        },
        
        ._clickLambda = [](ECS_Button&) {
            std::exit(69);
        },

        ._hoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.065f, 0.065f});
        },
        
        ._unHoverLambda = [](ECS_Button& comp) {
            Entity* entity = comp.get_parent();

            ECS_Index<ECS_Scaled> scaleIndex = comp.get_scale_index();

            if(!scaleIndex.is_success()) return;

            ECS_Scaled& scale = entity->ref_unsafe(scaleIndex);
            scale.set_scale(Vec2f{0.06f, 0.06f});
        }
    });

    add_static_entity<MainMenuParallaxBackground>();

    add_static_entity<AnimatedImage>((AnimatedImageProp) {
        ._texture = "logo_spritesheet",
        ._animation = "logo-animation",
        ._pos = Vec2f{-1.0f, 0.6f},
        ._scale = Vec2f{0.25f, 0.25f},
    });

    unbind();
}
