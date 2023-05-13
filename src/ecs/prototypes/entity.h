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

#include "uuid.h"

#include "ecs_component_container_index.tpp"
#include "ecs_component_container.tpp"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omniscia::core::ecs;

    enum EntityTimeType {
        STATIC,
        DYNAMIC
    };

    /**
     * @brief Entity - class used for storing components, 
     * managing their lifetime communication betweenn components and
    */
    class Entity {
        private:
            /**
             * @brief Entity UUID
            */
            UUID _uuid;

            /** @brief Container that holds all componets */
            ECS_ComponentContainer _component_container;

            EntityTimeType _timeType;
        
        public:
            /** @brief Default Entity constructor */
            Entity() {
                _uuid = UUID::gen_uuid();
                _timeType = DYNAMIC;
            }

            EntityTimeType get_time_type() const {
                return _timeType;
            }

            void set_time_type(const EntityTimeType& type) {
                _timeType = type;
            }

            /**
             * @brief Clones component container to 
             * specific entity instance
             * 
             * @param entity target, to which clone component container 
            */
            void clone_container_to(Entity& entity) const {
                entity._component_container = _component_container.clone();
            }
            
            /**
             * @brief Returns entity uuid
             *
             * @return entity uuid 
            */
            UUID get_uuid() const {
                return _uuid;
            }

            /**
             * @brief Method used for 
             * cloning Entity instances
             * 
             * @return new Entity instance 
            */
            virtual std::shared_ptr<Entity> clone() {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
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
                _component_container.add<T>(this);
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
                _component_container.add<T>(this, std::forward<Args>(args)...);
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
                return _component_container.ref_unsafe<T>(__index.get());
            }
            
            /**
             * @brief Method that time synchronizes all components of the
             * enityt instance
            */
            void time_sync() {
                _component_container.time_sync(this);
            }

            /**
             * @brief Indexes specific component by it type
             * 
             * @tparam T type of the needed component
             * @return ECS_Index<T> index of the retrieved component
             */
            template<typename T>
            ECS_Index<T> index() const {
                return _component_container.index<T>();
            }

            /**
             * @brief Function used for getting byte 
             * size of the entity(as well as 
             * counting all components)
             * 
             * @return u64 byte size 
            */
            u64 byte_size() const {
                return _component_container.byte_size();
            }
    };

    template<class T>
    class Predicate_EntityPrototypeEqual {
        public:
            bool operator()(const std::shared_ptr<omniscia::core::Entity>& entity) const {
                Entity* ptr = entity.get();

                if(dynamic_cast<T*>(ptr))
                    return true;

                return false; 
            }
    };

    class Predicate_EntityUUIDEqual {
        private:
            const UUID _uuid;
        
        public:
            Predicate_EntityUUIDEqual(const UUID& uuid) : _uuid(uuid) {

            }

            bool operator()(const std::shared_ptr<omniscia::core::Entity>& entity) const {
                Entity* ptr = entity.get();

                if(ptr->get_uuid() == _uuid)
                    return true;

                return false; 
            }
    };
}

#endif