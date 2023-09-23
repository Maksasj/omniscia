#include "ecs/controllers/ecs_clock_progression_bar_controller.h"
#include "game.h"

omniscia::core::ecs::ECS_ClockProgressionBarController::ECS_ClockProgressionBarController() : ECS_StateMachineBase() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
    switch_state<ECS_ClockProgressionBarController>(&ECS_ClockProgressionBarController::clock_progression_bar_update_state);
};

void omniscia::core::ecs::ECS_ClockProgressionBarController::time_sync() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_ClockProgressionBarController::reindex(void* parent) {
    _parent = (Entity*) parent;

    _spriteAnimationIndex = _parent->index<ECS_SpriteAnimationManual>();
}

void omniscia::core::ecs::ECS_ClockProgressionBarController::clock_progression_bar_update_state() {
    if(!_spriteAnimationIndex.is_success()) return;

    ECS_SpriteAnimationManual& spriteAnimationComp = _parent->ref_unsafe(_spriteAnimationIndex);

    const auto& timeLine = Game::get_instance().ref_time_line();

    const i64 frame = timeLine.get_actual_frame();
    const i64 size = timeLine.size();

    const f32 progression = frame / (f32) size;

    spriteAnimationComp.set_frame(trunc(7 * progression));
}
