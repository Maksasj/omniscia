/**
 * @file 
 * ecs_player_debug_metrics.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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

    /**
     * @brief ECS_PlayerDebugMetrics - component 
     * that sends all player metrics(position) to the
     * debug ui metrics data
    */
    class ECS_PlayerDebugMetrics : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> _posIndex;

        public:
            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            void reindex(void* parent) override;

            /**
             * @brief Default constructor of the ECS_PlayerDebugMetrics component
            */
            ECS_PlayerDebugMetrics();

            /**
             * @brief Method used for updating debug ui metrics, using player metrics(pos)
            */
            void update();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerDebugMetrics>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_PlayerDebugMetrics);
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
