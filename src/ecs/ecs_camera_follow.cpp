#include "ecs_camera_follow.h"

omniscia::core::ecs::ECS_CameraFollow::ECS_CameraFollow(const f32& cameraFollowSpeed) {
    ECS_CameraFollowSystem::get_instance().bind_component(this);
    
    _camPos = Vec3f{0.0, 0.0, 0.0};
    _cameraFollowSpeed = cameraFollowSpeed;
}

void omniscia::core::ecs::ECS_CameraFollow::time_sync() {
    ECS_CameraFollowSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_CameraFollow::reindex(void* parent) {
    _parent = (Entity*)parent;

    posIndex = _parent->index<ECS_Positioned>();
}

void omniscia::core::ecs::ECS_CameraFollow::update(Shader* shader) {
    if(!posIndex.is_success()) return;

    ECS_Positioned& posComp = _parent->ref_unsafe(posIndex);
    Vec3f& position = posComp.ref_pos();
    Vec3f delta = position - _camPos;

    f32 dt = Time::get_instance().get_delta_time();

    _camPos += delta * _cameraFollowSpeed * dt;

    shader->set_uniform_vec3f("cameraPosition", _camPos);
}

omniscia::core::Vec3f omniscia::core::ecs::ECS_CameraFollow::get_camera_pos() const {
    return _camPos;
}

omniscia::core::Vec3f& omniscia::core::ecs::ECS_CameraFollow::ref_camera_pos() {
    return _camPos;
}

f32 omniscia::core::ecs::ECS_CameraFollow::get_camera_follow_speed() const {
    return _cameraFollowSpeed;
}

f32& omniscia::core::ecs::ECS_CameraFollow::ref_camera_follow_speed() {
    return _cameraFollowSpeed;
}
