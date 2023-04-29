#include "ecs_camera_follow.h"

omniscia::core::ecs::ECS_CameraFollow::ECS_CameraFollow(const f32& cameraFollowSpeed) {
    ECS_CameraFollowSystem::get_instance().bind_component(this);
    
    _cameraFollowSpeed = cameraFollowSpeed;
}

void omniscia::core::ecs::ECS_CameraFollow::time_sync() {
    ECS_CameraFollowSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_CameraFollow::reindex(void* parent) {
    _parent = (Entity*)parent;

    posIndex = _parent->index<ECS_Positioned>();
}

void omniscia::core::ecs::ECS_CameraFollow::update() {
    if(!posIndex.is_success()) return;

    ECS_Positioned& posComp = _parent->ref_unsafe(posIndex);
    Vec3f position = posComp.get_pos();
    
    position.y += 0.3;

    Vec3f& camPos = Camera::get_instance().ref_pos();
    Vec3f delta = position - camPos;

    f32 dt = Time::get_instance().get_delta_time();

    camPos += delta * _cameraFollowSpeed * dt;

    DebugUI::get_instance().get_metrics()._cameraPos.x = camPos.x; 
    DebugUI::get_instance().get_metrics()._cameraPos.y = camPos.y; 
}

f32 omniscia::core::ecs::ECS_CameraFollow::get_camera_follow_speed() const {
    return _cameraFollowSpeed;
}

f32& omniscia::core::ecs::ECS_CameraFollow::ref_camera_follow_speed() {
    return _cameraFollowSpeed;
}
