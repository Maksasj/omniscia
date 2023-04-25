#include "main_menu_scene.h"
#include "game.h"

omniscia::core::MainMenuScene::MainMenuScene() : Scene() {
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
            ._texture = "options_button",
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
        ._pos = Vec2f{-1.3f, -0.2f},
        ._scale = Vec2f{0.06f, 0.06f},
        ._renderer = {
            ._texture = "quit_game_button",
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

    add_static_entity<MenuBackground>();

    unbind();
}
