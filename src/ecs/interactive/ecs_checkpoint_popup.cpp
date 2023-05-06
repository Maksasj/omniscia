#include "game.h"
#include "ecs_checkpoint_popup.h"

omniscia::core::ecs::ECS_CheckpointPopup::ECS_CheckpointPopup() 
        : ECS_Popup(0.2f, 0.1f, Vec2f{0.0f, 0.4f}, "popups", "save-popup-animation", 1000.0f, [&]() {
    Game::get_instance().save_dynamic_checkpoint();
}) {

}
