#ifndef _ECS_COMPONENT_TRIGGER_AABB_COLLIDER_H_
#define _ECS_COMPONENT_TRIGGER_AABB_COLLIDER_H_

#include <array>
#include <memory>
#include <iostream>
#include <algorithm>

#include "collision_side_type.h"
#include "ecs_box_collider_mesh.h"
#include "ecs_component.tpp"
#include "ecs_collision_mask.h"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "ecs_aabb_collider.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_TriggerAABBCollider : public ECS_AABBCollider {
        private:
            bool _isTriggered;

        public:
            ECS_TriggerAABBCollider(const u64& collisionLayer = CollisionMask_None, const u64& collisionLayerTarget = CollisionMask_None);

            void collide(ECS_AABBCollider* another) override;

            void reset_collisions() override;

            bool is_triggered() const {
                return _isTriggered;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_TriggerAABBCollider>(*this));
            }

            void _type_query(void* query) override {

            }
    };
}

#endif
