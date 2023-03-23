#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ecs_component_сontainer_index.tpp"
#include "ecs_component_сontainer.tpp"
#include "dynamic_object.h"

namespace omniscia::core {
    using namespace omniscia::core::ecs;

    class Entity : public DynamicObject {
        private:
            ECS_ComponentContainer _component_сontainer;
        public:
            Entity() {}

            void clone_container_to(Entity& entity) const {
                entity._component_сontainer = _component_сontainer.clone();
            }
            
            Entity clone() {
                Entity tmpEntity = *this;
                clone_container_to(tmpEntity);
                return tmpEntity;
            }

            template<typename T>
            Entity& add(T* component) {
                _component_сontainer.add(component, this);
                return *this;
            }

            template<typename T>
            T& ref_unsafe(ECS_Index<T> __index) const {
                return _component_сontainer.ref_unsafe<T>(__index.get());
            }
            
            void time_sync() {
                _component_сontainer.time_sync(this);
            }

            template<typename T>
            ECS_Index<T> index() const {
                return _component_сontainer.index<T>();
            }
    };
}

#endif