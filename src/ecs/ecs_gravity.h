#ifndef _ECS_COMPONENT_GRAVITY_H_
#define _ECS_COMPONENT_GRAVITY_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_Gravity : public ECS_Component {
        private:
            Entity* _parent;

            ECS_Index<ECS_Velocity> velocityIndex;
            ECS_Index<ECS_Acceleration> accelerationIndex;

            f32 _gravitationalAcceleration;
        public:
            void reindex(void* parent) override;
            void time_sync() override;

            ECS_Gravity();

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Gravity>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Gravity);
            }
    };

    class ECS_GravitySystem : public ECS_System<ECS_Gravity> {
        private:
            ECS_GravitySystem() {};
            ECS_GravitySystem(ECS_GravitySystem const&) {};
            void operator=(ECS_GravitySystem const&) {};
        public:
            void update() {
                for(ECS_Gravity* comp : _components) {
                    comp->update();
                }
            }

            static ECS_GravitySystem& get_instance() {
                static ECS_GravitySystem instance;
                return instance;
            }
    };
}

#endif
