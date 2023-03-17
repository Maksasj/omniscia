#ifndef _ECS_COMPONENT_CONTAINER_INDEX_H_
#define _ECS_COMPONENT_CONTAINER_INDEX_H_

#include <array>

#include "ecs_component.tpp"
#include "types.h"

namespace omniscia::core::ecs {
    template<typename T> 
    class ECS_Index {
        private:
            u32 _index;

            bool _success;
        public:
            ECS_Index() : _index(0) { _success = false; }
            ECS_Index(u32 index) : _index(index) { _success = true; }

            ECS_Index(bool success) {
                _success = success;
            }

            ECS_Index(void*) {
                _success = false;
            }

            bool is_success() {
                return _success;
            }

            u32 get() const {
                return _index;
            }    
    };
}

#endif