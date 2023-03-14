#ifndef _ECS_COMPONENT_H_
#define _ECS_COMPONENT_H_

#include <array>
#include <memory>
#include <iostream>

#include "types.h"

namespace omniscia::core::ecs {
    class ECS_Component {
        private:

        public:
            virtual ~ECS_Component() = default;

            virtual std::shared_ptr<ECS_Component> clone() { 
                return std::shared_ptr<ECS_Component>(NULL);
            }
    };
}

#endif