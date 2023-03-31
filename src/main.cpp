#include "game.h"

int main() {
    using namespace omniscia;
    
    /* Texture assets */
    TextureManager::get_instance().add_asset("assets/texture.png", "factorio_girl_texture");
    TextureManager::get_instance().add_asset("assets/jojo_texture.png", "jojo_texture");
    TextureManager::get_instance().add_asset("assets/player.png", "player");
    TextureManager::get_instance().add_asset("assets/player-spritesheet-export.png", "player-spritesheet");
    TextureManager::get_instance().add_asset("assets/background/1_layer.png", "1_layer");
    TextureManager::get_instance().add_asset("assets/background/2_layer.png", "2_layer");
    TextureManager::get_instance().add_asset("assets/background/3_layer.png", "3_layer");
    TextureManager::get_instance().add_asset("assets/background/4_layer.png", "4_layer");
    TextureManager::get_instance().check_assets();

    /* Shader assets */
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_1.glsl", "frag_stage_1", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_2.glsl", "frag_stage_2", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_3.glsl", "frag_stage_3", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_1.glsl", "vert_stage_1", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_2.glsl", "vert_stage_2", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_3.glsl", "vert_stage_3", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_background.glsl", "frag_stage_background", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_background.glsl", "vert_stage_background", VERTEX_SHADER);
    ShaderManager::get_instance().check_assets();

    Game game;
    game.load();
    game.run();

    return 0;
}
