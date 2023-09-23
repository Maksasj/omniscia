#include "ecs/motion/ecs_acceleration.h"

omniscia::core::ecs::ECS_Acceleration::ECS_Acceleration(const f32& aclX, const f32& aclY, const f32& aclZ) {
    _acl = Vec3f{aclX, aclY, aclZ};
}

omniscia::core::ecs::ECS_Acceleration::ECS_Acceleration(const Vec3f& acl) {
    _acl = acl;
}

void omniscia::core::ecs::ECS_Acceleration::reindex(void* parent) {

}

omniscia::core::Vec3f omniscia::core::ecs::ECS_Acceleration::get_acceleration() const {
    return _acl;
}

omniscia::core::Vec3f& omniscia::core::ecs::ECS_Acceleration::ref_acceleration() {
    return _acl;
}

void omniscia::core::ecs::ECS_Acceleration::add_acceleration(Vec3f force) {
    _acl += force;
}

void omniscia::core::ecs::ECS_Acceleration::set_acceleration(Vec3f aclocity) {
    _acl = aclocity;
}
