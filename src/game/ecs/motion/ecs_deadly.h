#ifndef _ECS_COMPONENT_DEADLY_H_
#define _ECS_COMPONENT_DEADLY_H_

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
#include "ecs/motion/ecs_trigger_aabb_collider.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_Deadly : public ECS_TriggerAABBCollider {
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Deadly>;

            void time_sync() override;

            ECS_Deadly();

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Deadly>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Deadly>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Deadly, _enabled, _isTriggered, _collisionLayer, _collisionLayerTarget, _colliding, _collisionPoint);

namespace omniscia::core::ecs {
    class ECS_DeadlySystem : public ECS_System<ECS_Deadly> {
        private:
            ECS_DeadlySystem() : ECS_System<ECS_Deadly>() {};
            ECS_DeadlySystem(ECS_DeadlySystem const&) {};
            void operator=(ECS_DeadlySystem const&) {};

        public:
            void update() {
                if(!_enabled)
                    return;

                bool _ = std::all_of(_components.begin(), _components.end(), [&](ECS_Deadly* comp) {
                    comp->update();
                    
                    if(DebugInfo::get_instance().get_metrics()._isTimeJump)
                        return false;
                    
                    return true;
                });
            }

            static ECS_DeadlySystem& get_instance() {
                static ECS_DeadlySystem instance;
                return instance;
            }
    };
}

#endif
