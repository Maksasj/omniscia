#include "chapter_choose_menu_scene.h"
#include "game.h"

omniscia::core::ChapterChooseMenuScene::ChapterChooseMenuScene() : Scene() {
    add_static_entity<Button>((ButtonProp) {
        ._pos = Vec2f{1.0f, -0.7f},
        ._scale = Vec2f{0.1f, 0.1f},
        ._renderer = {
            ._texture = "new_game_button",
            ._layer = 1,
        },
        
        ._clickLambda = [](ECS_Button&) {
            Game::get_instance().start_cutscene("transition_cutscene_to_game_scene");
            //Game::get_instance().start_cutscene("test_cutscene");
        },
    });

    add_static_entity<Background>((BackgroundProp) {
        ._texture = "chapter_choose_background",
        ._layer = 0,
    });

    unbind();
}
