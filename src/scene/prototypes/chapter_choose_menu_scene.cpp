#include "chapter_choose_menu_scene.h"
#include "game.h"

omniscia::core::ChapterChooseMenuScene::ChapterChooseMenuScene() : Scene() {
    // add_static_entity<BeachParallaxBackground>();
    add_static_entity<Button>(
    []() {
        Game::get_instance().start_cutscene("transition_cutscene_to_game_scene");
    },
    []() {

    });
    unbind();
}
