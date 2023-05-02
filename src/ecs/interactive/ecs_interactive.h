#ifndef _ECS_COMPONENT_INTERACTIVE_H_
#define _ECS_COMPONENT_INTERACTIVE_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_trigger_aabb_collider.h"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_Interactive : public ECS_Component {
        protected:
            Entity* _parent;

            std::function<void(void)> _lambda;
            f32 _cooldown;
            f32 _timer;

            ECS_Index<ECS_TriggerAABBCollider> _triggerColliderIndex;

        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_Interactive(const f32& cooldown, const std::function<void(void)>& lambda);
            // ECS_Interactive(const ECS_Interactive& instance) {
            //     _parent = instance._parent;
            //     _lambda = instance._lambda;
            //     _cooldown = instance._cooldown;
            //     _timer = instance._timer;
            //     _triggerColliderIndex = instance._triggerColliderIndex;
            // }

            virtual void update() {};

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Interactive>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Interactive);
            }
    };

    class ECS_InteractiveSystem : public ECS_System<ECS_Interactive> {
        private:
            ECS_InteractiveSystem() : ECS_System<ECS_Interactive>() {};
            ECS_InteractiveSystem(ECS_InteractiveSystem const&) {};
            void operator=(ECS_InteractiveSystem const&) {};

        public:
            void update() {
                if(!_enabled)
                    return;

                for(ECS_Interactive* comp : _components) {
                    comp->update();
                }
            }

            static ECS_InteractiveSystem& get_instance() {
                static ECS_InteractiveSystem instance;
                return instance;
            }
    };
}

#endif
