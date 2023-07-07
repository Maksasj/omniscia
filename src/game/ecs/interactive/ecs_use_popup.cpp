#include "game.h"
#include "ecs/interactive/ecs_use_popup.h"

omniscia::core::ecs::ECS_UsePopup::ECS_UsePopup(const std::string& cutsceneId) 
        : _cutsceneId(cutsceneId), ECS_Popup(0.2f, 0.1f, Vec2f{0.0f, 0.0f}, "popups", "use-popup-animation", 1000.0f, [&]() {
    Game::get_instance().start_cutscene(_cutsceneId);
}) {

}
