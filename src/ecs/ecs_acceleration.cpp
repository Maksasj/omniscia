#include "ecs_acceleration.h"

omniscia::core::ecs::ECS_Acceleration::ECS_Acceleration() { 
    _acl = Vec3f{0.0f, 0.0f, 0.0f}; 
}

omniscia::core::ecs::ECS_Acceleration::ECS_Acceleration(const Vec3f& acl) {
    _acl = acl;
}

void omniscia::core::ecs::ECS_Acceleration::reindex(void* parent) {

}

omniscia::core::Vec3f omniscia::core::ecs::ECS_Acceleration::get_acceleration() const {
    return _acl;
}

void omniscia::core::ecs::ECS_Acceleration::add_acceleration(Vec3f force) {
    _acl += force;
}

void omniscia::core::ecs::ECS_Acceleration::set_acceleration(Vec3f aclocity) {
    _acl = aclocity;
}
