#include "main_menu_scene.h"
#include "game.h"

omniscia::core::MainMenuScene::MainMenuScene() : Scene() {
    // add_static_entity<BeachParallaxBackground>();
    add_static_entity<Button>(
    []() {
        Game::get_instance().start_cutscene("transition_cutscene_to_chapter_choose_scene");
    },
    []() {

    });
    add_static_entity<MenuBackground>();

    unbind();
}
