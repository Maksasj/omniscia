#include "main_menu_scene.h"
#include "game.h"

omniscia::core::MainMenuScene::MainMenuScene() : Scene() {
    // add_static_entity<BeachParallaxBackground>();
    add_static_entity<Button>(
    []() {
        Game::get_instance().switch_scene("game_scene");
        std::cout << "poggers\n";
    },
    []() {

    });
    unbind();
}
