#include "game.h"

int main() {
    srand(time(NULL));
    using namespace omniscia;
    
    /* Texture assets */
    TextureManager::get_instance().add_asset("assets/texture.png", "factorio_girl_texture");
    TextureManager::get_instance().add_asset("assets/jojo_texture.png", "jojo_texture");
    TextureManager::get_instance().add_asset("assets/player.png", "player");
    TextureManager::get_instance().add_asset("assets/background/1_layer.png", "1_layer");
    TextureManager::get_instance().add_asset("assets/background/2_layer.png", "2_layer");
    TextureManager::get_instance().add_asset("assets/background/3_layer.png", "3_layer");
    TextureManager::get_instance().add_asset("assets/background/4_layer.png", "4_layer");
    TextureManager::get_instance().add_asset("assets/background/4_layer.png", "4_layer");
    TextureManager::get_instance().add_asset("assets/entities/player.png", "player-spritesheet");
    TextureManager::get_instance().add_asset("assets/entities/crab.png", "crab-spritesheet");
    TextureManager::get_instance().add_asset("assets/tiles/test_tiles.png", "test_tiles");
    TextureManager::get_instance().add_asset("assets/background/beach/beach.png", "background_beach_beach_layer");
    TextureManager::get_instance().add_asset("assets/background/beach/grass_overlay.png", "background_beach_grass_overlay_layer");
    TextureManager::get_instance().add_asset("assets/background/beach/sky1.png", "background_beach_sky1_layer");
    TextureManager::get_instance().add_asset("assets/background/beach/sky2.png", "background_beach_sky2_layer");
    TextureManager::get_instance().add_asset("assets/background/beach/terrain.png", "background_beach_terrain_layer");
    try {
        TextureManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    /* Shader assets */
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_1.glsl", "frag_stage_1", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_2.glsl", "frag_stage_2", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_3.glsl", "frag_stage_3", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_1.glsl", "vert_stage_1", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_2.glsl", "vert_stage_2", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_3.glsl", "vert_stage_3", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_background.glsl", "frag_stage_background", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_background.glsl", "vert_stage_background", VERTEX_SHADER);
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
    
    try {
        Game::get_instance().load();
    } catch(const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    Game::get_instance().run();

    return 0;
}
