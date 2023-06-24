/**
 * @file 
 * ecs_component.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_H_
#define _ECS_COMPONENT_H_

#include <array>
#include <memory>
#include <iostream>
#include <sstream>

#include "omni_reflector.h"

#include "omni_types.tpp"

#include "debug_field_query.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omni::reflector;

    /**
     * @brief ECS_Component - generic class 
     * used for all components, just 
     * declares some virtual generall methods
    */
    class ECS_Component {
        private:

        protected:
            bool _enabled;

        public:
            /** @brief Destroy the ecs component object */
            virtual ~ECS_Component() = default;

            void enable() {
                _enabled = true;
            }

            void disable() {
                _enabled = false;
            }

            bool is_enabled() const {
                return _enabled;
            }

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            virtual void time_sync() {}

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            virtual void reindex(void* parent) {};

            /**
             * @brief Virtual method used for 
             * binding component to his system
            */
            virtual void bind_parent(void*) {};

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            virtual std::shared_ptr<ECS_Component> clone() { 
                return std::shared_ptr<ECS_Component>(NULL);
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            virtual void _type_query(void* query) {

            }
    };
}

#endif