#include "ecs_player_time_jump_controller.h"

/* NOTE */
#include "game.h"

omniscia::core::ecs::ECS_PlayerTimeJumpController::ECS_PlayerTimeJumpController() {
    ECS_PlayerTimeJumpControllerSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerTimeJumpController::time_sync() {
    ECS_PlayerTimeJumpControllerSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_PlayerTimeJumpController::update() {
    static u64 frame = 0;
    ++frame;

    auto& gameInstance = Game::get_instance();
    auto& timeLine = gameInstance.ref_time_line();
    bool& isTimeJump = DebugUI::get_instance().get_metrics()._isTimeJump;
    DebugUI::get_instance().get_metrics()._timeCurrentLineLength = timeLine.get_index();
    isTimeJump = !Controls::get_instance().get(PlayerController::TIME_JUMP); 

    if(frame % 5 != 0) return;

    Scene* activeScene = gameInstance.get_active_scene();

    if(isTimeJump) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        activeScene->ref_dynamic_part() = timeLine.get();
        activeScene->time_sync();
        timeLine.pop();

        DebugUI::get_instance().get_metrics()._timeCurrentLineLength = timeLine.get_index();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        DebugUI::get_instance().get_metrics()._timeManipulationTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 0.000001;
    } else {
        timeLine.push(activeScene->clone());
    }
}
