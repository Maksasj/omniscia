#include "ecs_player_time_jump_controller.h"

/* NOTE */
#include "game.h"

omniscia::core::ecs::ECS_PlayerTimeJumpController::ECS_PlayerTimeJumpController() {
    ECS_PlayerTimeJumpControllerSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerTimeJumpController::update() {
    static u64 frame = 0;
    ++frame;

    auto& gameInstance = Game::get_instance();
    auto& timeLine = gameInstance.ref_time_line();
    bool& isTimeJump = DebugUI::get_instance().get_metrics()._isTimeJump;
    DebugUI::get_instance().get_metrics()._timeCurrentLineLength = timeLine.size();
    isTimeJump = !Controls::get(PlayerController::TIME_JUMP); 

    if(frame % 5 != 0) return;

    Scene* activeScene = gameInstance.get_active_scene();

    if(isTimeJump) {
        if(timeLine.size() > 0) {
            activeScene->ref_dynamic_part() = timeLine[timeLine.size() - 1];
            activeScene->time_sync();
            timeLine.pop_back();
            DebugUI::get_instance().get_metrics()._timeCurrentLineLength = timeLine.size();
        }
    } else {
        timeLine.push_back(activeScene->clone());
        if(timeLine.size() >= 5000) {
            timeLine.pop_front();
        }
    }
}
