#include "game.h"

int main() {
    srand(time(NULL));
    using namespace omniscia;
    using namespace omni::types;
    
    TextureManager::get_instance().add_assets("assets/texture_assets.json");

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

    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_gui.glsl", "vert_stage_gui", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_gui.glsl", "frag_stage_gui", FRAGMENT_SHADER);
    try {
        ShaderManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    /* Animation assets */
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.125}, {0.0, 0.75},    7, true, 5,     true}), "player-run-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.125}, {0.0, 0.875},   7, true, 12,    true}), "player-idle-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.125}, {0.0, 0.625},   7, true, 12,    true}), "player-fly-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.125}, {0.0, 0.5},     8, true, 12,    false}), "player-death-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.5},   {0.0, 0.5},     8, true, 24,    true}), "crab-idle-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.5},   {0.0, 0.0},     8, true, 12,    true}), "crab-run-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.125}, {0.0, 0.875},   7, true, 24,    true}), "grandpa-idle-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.0625},{0.0, 0.9375},  6, true, 8,     true}), "use-popup-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.0625},{0.0, 0.875},   6, true, 8,     true}), "speak-popup-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.0625},{0.0, 0.75},    6, true, 8,     true}), "save-popup-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 1.0},   {0.0, 0.0},     6, true, 12,    true}), "checkpoint-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 1.0},   {0.0, 0.0},     6, true, 12,    true}), "logo-animation");
    
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.5},   {0.0, 0.5},     6, true, 12,    true}), "star-spinning-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.5},   {0.0, 1.0},     8, true, 12,    true}), "star-shiny-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 1.0},   {0.0, 0.0},     8, true, 12,    true}), "clock-bar-progression-animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 1.0},   {0.0, 0.0},     6, true, 24,    true}), "red-crystal-idle-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 1.0},   {0.0, 0.0},     6, true, 36,    true}), "chapter-1-thumbnail-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.2, 1.0},     {0.0, 0.0},     5, true, 48,    true}), "fireflies_animation");
    
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.0, 0.75},    1, true, 48,    false}), "chapter_1_locked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.5, 0.75},    1, true, 48,    false}), "chapter_1_unlocked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.0, 0.5},    1, true, 48,    false}), "chapter_2_locked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.5, 0.5},    1, true, 48,    false}), "chapter_2_unlocked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.0, 0.25},    1, true, 48,    false}), "chapter_3_locked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.5, 0.25},    1, true, 48,    false}), "chapter_3_unlocked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.0, 0.0},    1, true, 48,    false}), "chapter_4_locked_animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.5, 0.25},     {0.5, 0.0},    1, true, 48,    false}), "chapter_4_unlocked_animation");

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0},  {0.125, 0.5},   {0.0, 0.5},     8, true, 12,    true}), "selector-animation");


    /* Sound assets */
    SoundManager::get_instance().add_assets("assets/sound_assets.json");
    try {
        omniscia::core::SoundManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }
    
    LevelAssetManager::get_instance().add_asset("assets/levels/level.json", "test_level", BASE);
    try {
        LevelAssetManager::get_instance().check_assets();
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << "\n";
        return 1;
    }

    FontManager::get_instance().add_asset("assets/textures/fonts/soft-dark.png", "test_font",                           { ' ', 16, Vec2f::splat(0.0625f) } );
    FontManager::get_instance().add_asset("assets/textures/fonts/soft-thick.png", "test_font_another",                  { ' ', 16, Vec2f::splat(0.0625f) } );
    FontManager::get_instance().add_asset("assets/textures/fonts/abaddon-light-white.png", "abaddon-light-white",       { ' ', 16, Vec2f::splat(0.0625f) } );
    FontManager::get_instance().add_asset("assets/textures/fonts/dejavu-sans-mono-white.png", "dejavu-sans-mono-white", { ' ', 16, Vec2f::splat(0.0625f) } );
    FontManager::get_instance().add_asset("assets/textures/fonts/monogram-white.png", "monogram-white",                 { ' ', 16, Vec2f::splat(0.0625f) } );
    FontManager::get_instance().add_asset("assets/textures/fonts/monogram-gray.png", "monogram-gray",                   { ' ', 16, Vec2f::splat(0.0625f) } );
    FontManager::get_instance().add_asset("assets/textures/fonts/yoster-white.png", "yoster-white",                     { ' ', 16, Vec2f::splat(0.0625f) } );
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

