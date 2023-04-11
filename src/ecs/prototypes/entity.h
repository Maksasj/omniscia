/**
 * @file 
 * entity.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ecs_component_сontainer_index.tpp"
#include "ecs_component_сontainer.tpp"

namespace omniscia::core {
    using namespace omniscia::core::ecs;

    /**
     * @brief Entity - class used for storing components, 
     * managing their lifetime communication betweenn components and
    */
    class Entity {
        private:
            /** @brief Container that holds all componets */
            ECS_ComponentContainer _component_сontainer;
        
        public:
            /** @brief Default Entity constructor */
            Entity() {}

            /**
             * @brief Clones component container to 
             * specific entity instance
             * 
             * @param entity target, to which clone component container 
            */
            void clone_container_to(Entity& entity) const {
                entity._component_сontainer = _component_сontainer.clone();
            }
            
            /**
             * @brief Method used for 
             * cloning Entity instances
             * 
             * @return new Entity instance 
            */
            Entity clone() {
                Entity tmpEntity = *this;
                clone_container_to(tmpEntity);
                return tmpEntity;
            }

            /**
             * @brief Add component to an component container
             * nad reindexes all components
             * 
             * @tparam T - type of the component
             * @return reference to the current entity instance(used for method chaining)
            */
            template<class T>
            Entity& add() {
                _component_сontainer.add<T>(this);
                return *this;
            }

            /**
             * @brief Add component to an component container
             * nad reindexes all components
             * 
             * @tparam T - type of the component 
             * @tparam Args type of the arguments
             * @param args arguments of the component container
             * @return reference to the current entity instance(used for method chaining)
            */
            template<class T, class... Args>
            Entity& add(Args&&... args) {
                _component_сontainer.add<T>(this, std::forward<Args>(args)...);
                return *this;
            }

            /**
             * @brief References specific component by it ecs_index
             * 
             * @tparam T type of the component
             * @param __index ecs_index of the component
             * @return T& reference to the component
            */
            template<typename T>
            T& ref_unsafe(ECS_Index<T> __index) const {
                return _component_сontainer.ref_unsafe<T>(__index.get());
            }
            
            /**
             * @brief Method that time synchronizes all components of the
             * enityt instance
            */
            void time_sync() {
                _component_сontainer.time_sync(this);
            }

            /**
             * @brief Indexes specific component by it type
             * 
             * @tparam T type of the needed component
             * @return ECS_Index<T> index of the retrieved component
             */
            template<typename T>
            ECS_Index<T> index() const {
                return _component_сontainer.index<T>();
            }

            /**
             * @brief Function used for getting byte 
             * size of the entity(as well as 
             * counting all components)
             * 
             * @return u64 byte size 
            */
            u64 byte_size() const {
                return _component_сontainer.byte_size();
            }
    };
}

#endif