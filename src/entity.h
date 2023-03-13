#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ecs_component_сontainer.tpp"
#include "ecs_component_сontainer_index.tpp"
#include "dynamic_object.h"

namespace omniscia::core {
    using namespace omniscia::core::ecs;

    template<u32 _ecs_size>
    class Entity : public DynamicObject {
        protected:
            ECS_ComponentContainer<_ecs_size> component_сontainer;
        public:
            Entity() {}

            template<typename T>
            T clone() const {
                T entity = *((T*)this);
                
                entity.component_сontainer = component_сontainer.clone();

                return entity;
            }

            template<typename T>
            std::shared_ptr<T> ref(const ECS_Index<T>& index) {
                return std::static_pointer_cast<T>(component_сontainer.at(index.get()));
            }

            //template<typename T>
            //std::shared_ptr<T> add_and_ref(const T& component) {
            //    return component_сontainer.add_and_ref(component);
            //}

            /*
            template<typename T>
            T clone() const {
                auto entity = new Entity();
                entity->component_сontainer = component_сontainer.clone();
                //return std::make_shared<Entity<_ecs_size>>(*this);
                return std::shared_ptr<Entity<_ecs_size>>(entity);
            }
            */

            //Entity<_ecs_size> clone() const {
            //    return std::make_shared<Entity<_ecs_size>>(*this);
            //}

            //template<typename T>
            //T clone() const {
            //    T entity = *(T*)this;
            //    entity.component_сontainer = this->component_сontainer;
            //    return entity;
            //}
    };
}

#endif