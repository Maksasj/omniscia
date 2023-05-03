#include "game.h"

int main() {
    srand(time(NULL));
    using namespace omniscia;
    
    /* Texture assets */
    TextureManager::get_instance().add_asset("assets/textures/texture.png", "factorio_girl_texture");
    TextureManager::get_instance().add_asset("assets/textures/jojo_texture.png", "jojo_texture");

    TextureManager::get_instance().add_asset("assets/textures/entities/characters/player/player.png", "player-spritesheet");
    TextureManager::get_instance().add_asset("assets/textures/entities/characters/grandpa/grandpa.png", "grandpa-spritesheet");
    TextureManager::get_instance().add_asset("assets/textures/entities/crab/crab.png", "crab-spritesheet");
    TextureManager::get_instance().add_asset("assets/textures/entities/checkpoint/checkpoint-spritesheet.png", "checkpoint-spritesheet");

    TextureManager::get_instance().add_asset("assets/textures/tiles/beach/beach_tiles.png", "beach_tiles");
    TextureManager::get_instance().add_asset("assets/textures/background/beach/beach.png", "background_beach_beach_layer");
    TextureManager::get_instance().add_asset("assets/textures/background/beach/grass_overlay.png", "background_beach_grass_overlay_layer");
    TextureManager::get_instance().add_asset("assets/textures/background/beach/sky1.png", "background_beach_sky1_layer");
    TextureManager::get_instance().add_asset("assets/textures/background/beach/sky2.png", "background_beach_sky2_layer");
    TextureManager::get_instance().add_asset("assets/textures/background/beach/terrain.png", "background_beach_terrain_layer");
    
    TextureManager::get_instance().add_asset("assets/textures/ui/dialogue.png", "dialogue");
    TextureManager::get_instance().add_asset("assets/textures/ui/icons/grandpa_test_icon.png", "grandpa_test_icon");
    TextureManager::get_instance().add_asset("assets/textures/ui/icons/player_test_icon.png", "player_test_icon");
    TextureManager::get_instance().add_asset("assets/textures/ui/popup/popups.png", "popups");

    TextureManager::get_instance().add_asset("assets/textures/background/menu/menu_background.png", "menu_background");
    TextureManager::get_instance().add_asset("assets/textures/background/menu/continue_button.png", "continue_button");
    TextureManager::get_instance().add_asset("assets/textures/background/menu/new_game_button.png", "new_game_button");
    TextureManager::get_instance().add_asset("assets/textures/background/menu/options_button.png", "options_button");
    TextureManager::get_instance().add_asset("assets/textures/background/menu/quit_game_button.png", "quit_game_button");
    TextureManager::get_instance().add_asset("assets/textures/background/menu/secrets_button.png", "secrets_button");

    TextureManager::get_instance().add_asset("assets/textures/background/chapter_choose/chapter_choose_background.png", "chapter_choose_background");
    TextureManager::get_instance().add_asset("assets/textures/background/secrets/secrets_background.png", "secrets_background");
    TextureManager::get_instance().add_asset("assets/textures/background/settings/settings_background.png", "settings_background");
    
    try {
        TextureManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    /* Shader assets */
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_main.glsl", "frag_stage_main", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_main.glsl", "vert_stage_main", VERTEX_SHADER);

    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_intermediate.glsl", "frag_stage_intermediate", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_intermediate.glsl", "vert_stage_intermediate", VERTEX_SHADER);
    
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_late.glsl", "frag_stage_late", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_late.glsl", "vert_stage_late", VERTEX_SHADER);
    
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_background.glsl", "frag_stage_background", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_background.glsl", "vert_stage_background", VERTEX_SHADER);
    
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_final.glsl", "frag_stage_final", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_final.glsl", "vert_stage_final", VERTEX_SHADER);
    
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_transition.glsl", "vert_stage_transition", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_transition.glsl", "frag_stage_transition", FRAGMENT_SHADER);
    try {
        ShaderManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    /* Animation assets */
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.125}, {0.0, 0.75}, 7, true, 5}), "player-run-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.125}, {0.0, 0.875}, 7, true, 12}), "player-idle-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.5}, {0.0, 0.5}, 8, true, 24}), "crab-idle-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.5}, {0.0, 0.0}, 8, true, 12}), "crab-run-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.125}, {0.0, 0.875}, 7, true, 24}), "grandpa-idle-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.0625}, {0.0, 0.9375}, 6, true, 8}), "use-popup-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.0625}, {0.0, 0.875}, 6, true, 8}), "speak-popup-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.0625}, {0.0, 0.75}, 6, true, 8}), "save-popup-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 1.0}, {0.0, 0.0}, 6, true, 12}), "checkpoint-animation");
    
    /* Sound assets */
    omniscia::core::SoundManager::get_instance().add_asset("assets/sounds/walk/walk1.wav", "walk_1");
    omniscia::core::SoundManager::get_instance().add_asset("assets/sounds/walk/walk2.wav", "walk_2");
    omniscia::core::SoundManager::get_instance().add_asset("assets/sounds/walk/walk3.wav", "walk_3");
    omniscia::core::SoundManager::get_instance().add_asset("assets/sounds/walk/walk4.wav", "walk_4");
    try {
        omniscia::core::SoundManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }
    
    LevelAssetManager::get_instance().add_asset("assets/levels/level.bin", "test_level", BASE);
    try {
        LevelAssetManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    FontManager::get_instance().add_asset("assets/textures/fonts/soft-dark.png", "test_font", {' ', 16, Vec2f{0.0625f, 0.0625f}});
    FontManager::get_instance().add_asset("assets/textures/fonts/soft-thick.png", "test_font_another", { ' ', 16, Vec2f{0.0625f, 0.0625f} } );
    FontManager::get_instance().add_asset("assets/textures/fonts/abaddon-light-white.png", "abaddon-light-white", { ' ', 16, Vec2f{0.0625f, 0.0625f} } );
    FontManager::get_instance().add_asset("assets/textures/fonts/dejavu-sans-mono-white.png", "dejavu-sans-mono-white", { ' ', 16, Vec2f{0.0625f, 0.0625f} } );
    FontManager::get_instance().add_asset("assets/textures/fonts/monogram-white.png", "monogram-white", { ' ', 16, Vec2f{0.0625f, 0.0625f} } );
    FontManager::get_instance().add_asset("assets/textures/fonts/yoster-white.png", "yoster-white", { ' ', 16, Vec2f{0.0625f, 0.0625f} } );
    try {
        FontManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    try {
        Game::get_instance().load();
    } catch(const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    auto saves = SaveLoader::get_instance().scan_for_saves("assets/saves");
    SaveLoader::get_instance().validate_saves(saves);
    if(saves.empty()) {
        std::cout << "There is no saves !\n";
    }

    try {
        SaveManager::get_instance().load_save(saves[0]);
    } catch(const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    Game::get_instance().run();

    return 0;
}
