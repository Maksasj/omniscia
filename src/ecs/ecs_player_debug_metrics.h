#ifndef _ECS_COMPONENT_PLAYER_DEBUG_METRICS_H_
#define _ECS_COMPONENT_PLAYER_DEBUG_METRICS_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_system.h"
#include "ecs_positioned.h"

#include "debug_ui.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerDebugMetrics : public ECS_Component {
        private:
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Positioned> _posIndex;
        public:
            ECS_PlayerDebugMetrics(Entity& parent);

            void reindex(void* parent) override;
            void time_sync() override;

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerDebugMetrics>(*this));
            }
    };

    class ECS_PlayerDebugMetricsSystem : public ECS_System<ECS_PlayerDebugMetrics> {
        private:
            ECS_PlayerDebugMetricsSystem() {};
            ECS_PlayerDebugMetricsSystem(ECS_PlayerDebugMetricsSystem const&) {};
            void operator=(ECS_PlayerDebugMetricsSystem const&) {};
        public:
            void update() {
                for(ECS_PlayerDebugMetrics* comp : _components) {
                    comp->update();
                }
            }

            static ECS_PlayerDebugMetricsSystem& get_instance() {
                static ECS_PlayerDebugMetricsSystem instance;
                return instance;
            }
    };
}

#endif
