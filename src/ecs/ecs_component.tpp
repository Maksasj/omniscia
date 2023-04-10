#ifndef _ECS_COMPONENT_H_
#define _ECS_COMPONENT_H_

#include <array>
#include <memory>
#include <iostream>

#include "types.tpp"

namespace omniscia::core::ecs {
    class ECS_Component {
        protected:

        public:
            virtual ~ECS_Component() = default;

            virtual void reindex(void* parent) {};

            virtual void bind_parent(void*) {};

            virtual void time_sync() {}

            virtual std::shared_ptr<ECS_Component> clone() { 
                return std::shared_ptr<ECS_Component>(NULL);
            }

            virtual u64 byte_size() {
                return sizeof(ECS_Component);
            }
    };
}

#endif