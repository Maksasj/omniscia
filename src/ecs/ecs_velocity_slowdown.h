#ifndef _ECS_COMPONENT_VELOCITY_SLOWDOWN_H_
#define _ECS_COMPONENT_VELOCITY_SLOWDOWN_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_system.h"
#include "ecs_velocity.h"
#include "ecs_component.tpp"
#include "controls.h"

#define DEFAULT_GRAVITATION_ACCELERATION 9.8

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_VelocitySlowdown : public ECS_Component {
        private:
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Velocity> velocityIndex;
        public:
            ECS_VelocitySlowdown(Entity& parent);

            void reindex(void* parent) override;
            void time_sync() override;

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_VelocitySlowdown>(*this));
            }
    };

    class ECS_VelocitySlowdownSystem : public ECS_System<ECS_VelocitySlowdown> {
        private:
            ECS_VelocitySlowdownSystem() {};
            ECS_VelocitySlowdownSystem(ECS_VelocitySlowdownSystem const&) {};
            void operator=(ECS_VelocitySlowdownSystem const&) {};
        public:
            void update() {
                for(ECS_VelocitySlowdown* comp : _components) {
                    comp->update();
                }
            }

            static ECS_VelocitySlowdownSystem& get_instance() {
                static ECS_VelocitySlowdownSystem instance;
                return instance;
            }
    };
}

#endif
