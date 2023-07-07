#include "ecs/sound/ecs_sound_emitter.h"

omniscia::core::ecs::ECS_SoundEmitter::ECS_SoundEmitter() {
    ECS_SoundEmitterSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_SoundEmitter::time_sync() {
    ECS_SoundEmitterSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_SoundEmitter::reindex(void* parent) {
    _parent = (Entity*)parent;

    _posIndex = _parent->index<ECS_Positioned>();
}

void omniscia::core::ecs::ECS_SoundEmitter::update() {
    if(!_posIndex.is_success()) return;

    ECS_Positioned& posComp = _parent->ref_unsafe(_posIndex);

    _speaker.set_pos(posComp.ref_pos().x, posComp.ref_pos().y);
    _speaker.update();
}

void omniscia::core::ecs::ECS_SoundEmitter::play(const std::string& soundId) {
    _speaker.play(soundId);
}
