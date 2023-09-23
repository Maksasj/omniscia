#ifndef _ECS_COMPONENT_TRIGGER_AABB_COLLIDER_H_
#define _ECS_COMPONENT_TRIGGER_AABB_COLLIDER_H_

#include <array>
#include <memory>
#include <iostream>
#include <algorithm>

#include "collision_side_type.h"
#include "ecs/motion/ecs_box_collider_mesh.h"
#include "ecs/ecs_component.tpp"
#include "ecs_collision_mask.h"
#include "ecs/motion/ecs_positioned.h"
#include "ecs/ecs_system.h"
#include "ecs/motion/ecs_scaled.h"
#include "controls.h"
#include "ecs/entity.h"
#include "ecs/motion/ecs_aabb_collider.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_TriggerAABBCollider : public ECS_AABBCollider {
        protected:
            bool _isTriggered;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_TriggerAABBCollider>;

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
                DebugFieldQuery::debug_component_edit_query<ECS_TriggerAABBCollider>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_TriggerAABBCollider, _enabled, _isTriggered, _collisionLayer, _collisionLayerTarget, _colliding, _collisionPoint);

#endif
