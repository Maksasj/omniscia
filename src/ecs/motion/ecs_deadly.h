#ifndef _ECS_COMPONENT_DEADLY_H_
#define _ECS_COMPONENT_DEADLY_H_

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
#include "ecs_trigger_aabb_collider.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_Deadly : public ECS_TriggerAABBCollider {
        public:
            void time_sync() override;

            ECS_Deadly();

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Deadly>(*this));
            }
    };

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
