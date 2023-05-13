#include "game.h"
#include "ecs_speak_popup.h"

omniscia::core::ecs::ECS_SpeakPopup::ECS_SpeakPopup(const std::string& dialogueCutsceneId) 
        : _dialogueCutsceneId(dialogueCutsceneId), ECS_Popup(0.2f, 0.1f, Vec2f{0.0f, 0.0f}, "popups", "speak-popup-animation", 1000.0f, [&]() {
    Game::get_instance().start_cutscene("test_dialogue_cutscene");
}) {

}

omniscia::core::ecs::ECS_SpeakPopup::ECS_SpeakPopup(ECS_SpeakPopup const& comp)
    : _dialogueCutsceneId(comp._dialogueCutsceneId), ECS_Popup(comp) {

}
