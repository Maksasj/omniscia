#include "game.h"
#include "ecs/interactive/ecs_red_crystal_popup.h"

omniscia::core::ecs::ECS_RedCrystalPopup::ECS_RedCrystalPopup() 
        : ECS_Popup(0.2f, 0.1f, Vec2f{0.0f, 0.3f}, "popups", "use-popup-animation", 1000.0f, [&]() {
    Game::get_instance().start_cutscene("chapter_1_end_cutscene");
}) {

}
