#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ecs_component_сontainer.tpp"
#include "ecs_component_сontainer_index.tpp"
#include "dynamic_object.h"

namespace omniscia::core {
    using namespace omniscia::core::ecs;

    class Entity : public DynamicObject {
        private:
            ECS_ComponentContainer _component_сontainer;
        public:
            Entity() {}

            /* ECS COMPONENT CONTAINER MANAGMENT */
            void clone_container_to(Entity& entity) const {
                entity._component_сontainer = _component_сontainer.clone();
            }

            /* Add and return index */
            template<typename T>
            ECS_Index<T> add_and_index(std::shared_ptr<T> component) {
                return _component_сontainer.add_and_index(component);
            }

            template<typename T>
            ECS_Index<T> add_and_index(const T& component) {
                return _component_сontainer.add_and_index(component);
            }

            /* Add */
            template<typename T>
            void add(std::shared_ptr<T> component) {
                _component_сontainer.add(component);
            }

            template<typename T>
            void add(const T& component) {
                _component_сontainer.add(component);
            }

            /* Get by type*/
            template<typename T>
            std::optional<std::shared_ptr<T>> try_get() const {
                return _component_сontainer.get<T>();
            }

            template<typename T>
            std::shared_ptr<T> get_unsafe() const {
                return _component_сontainer.get_unsafe<T>();
            }

            /* Reference component directly */
            template<typename T>
            std::optional<std::reference_wrapper<T>> try_ref() const {
                return _component_сontainer.ref<T>();
            }

            template<typename T>
            T& ref_unsafe() const {
                return _component_сontainer.ref_unsafe<T>();
            }

            template<typename T>
            std::optional<std::reference_wrapper<T>> try_ref(ECS_Index<T> __index) const {
                return _component_сontainer.ref<T>(__index.get());
            }

            template<typename T>
            T& ref_unsafe(ECS_Index<T> __index) const {
                return _component_сontainer.ref_unsafe<T>(__index.get());
            }

            /* Index by index / get by index */
            template<typename T>
            std::optional<std::shared_ptr<T>> try_index(const ECS_Index<T>& __index) const {
                return _component_сontainer.index<T>(__index.get());
            }

            template<typename T>
            std::shared_ptr<T> index_unsafe(const ECS_Index<T>& index) const {
                return _component_сontainer.index_unsafe<T>(index.get());
            }

            /* Utils */
            template<typename T>
            bool has() const {
                return _component_сontainer.has<T>();
            }
            
            u32 ecs_container_size() const {
                return _component_сontainer.size();
            }
    };
}

#endif