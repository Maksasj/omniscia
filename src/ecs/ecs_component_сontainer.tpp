#ifndef _ECS_COMPONENT_CONTAINER_H_
#define _ECS_COMPONENT_CONTAINER_H_

#include <vector>
#include <cassert>
#include <optional>

#include "ecs_component_сontainer_index.tpp"
#include "ecs_component.tpp"
#include "types.tpp"

namespace omniscia::core::ecs {
    class ECS_ComponentContainer {
        private:
            std::vector<std::shared_ptr<ECS_Component>> _components;
        public:
            ECS_ComponentContainer() {
                //_components = std::vector<std::shared_ptr<ECS_Component>>;
            }

            ECS_ComponentContainer clone() const {
                ECS_ComponentContainer cont;

                for(auto &c : _components) {
                    cont._components.push_back(c->clone());
                }

                return cont;
            }

            template<typename T>
            T& ref_unsafe(u32 index) const {
                return *std::dynamic_pointer_cast<T>(_components[index]);
            }

            template<typename T>
            void add(T* component, void* parent) {
                std::shared_ptr<T> ptr(component); //TODO better to replace with referencing but need to fing how, since std::make_shared creates new instance
                ptr->reindex(parent);               
                _components.push_back(ptr);
            }

            void time_sync(void* parent) {
                for(auto &c : _components) {
                    c->reindex(parent);
                    c->time_sync();
                }
            }

            template<typename T>
            ECS_Index<T> index() const {
                for(u32 i = 0; i < _components.size(); ++i) {
                    if(std::dynamic_pointer_cast<T>(_components[i])) {
                        return ECS_Index<T>(i);
                    }
                }

                return ECS_Index<T>(nullptr);
            }

            /* Utils */
            template<typename T>
            bool has() const {
                for(auto &c : _components) {
                    if(std::dynamic_pointer_cast<T>(c))
                        return true;
                }

                return false;
            }

            u32 size() const {
                return _components.size();
            }
    };
}

#endif