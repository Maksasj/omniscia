#ifndef _ECS_COMPONENT_CONTAINER_H_
#define _ECS_COMPONENT_CONTAINER_H_

#include <array>

#include "ecs_component_сontainer_index.tpp"
#include "ecs_component.tpp"
#include "types.h"

namespace omniscia::core::ecs {
    template<u32 _size> 
    class ECS_ComponentContainer { //Akka my array
        private:
            std::array<std::shared_ptr<ECS_Component>, _size> _components;
            u32 _lastIndex;
        public:
            ECS_ComponentContainer() : _lastIndex(0) {}

            ECS_ComponentContainer<_size> clone() const {
                ECS_ComponentContainer<_size> container;

                for(int i = 0; i < _lastIndex; ++i) {
                    container._components[i] = std::make_shared<ECS_Component>(*(container._components[i].get()));
                }

                return container;
            }

            template<typename T>
            void add(std::shared_ptr<T> ptr) {
                _components[_lastIndex++] = ptr;

                if(_lastIndex >= _size)
                    throw std::exception("ECS_ComponentContainer near overflow");
            }

            std::shared_ptr<ECS_Component>& at(u32 index) {
                return _components[index];
            }
            
            u32 size() {
                return _lastIndex;
            }

            template<typename T>
            std::shared_ptr<T> add_and_ref(std::shared_ptr<T> ptr) {
                _components[_lastIndex++] = ptr;

                if(_lastIndex >= _size)
                    throw std::exception("ECS_ComponentContainer near overflow");

                return ptr;
            }

            template<typename T>
            ECS_Index<T> add_and_index(std::shared_ptr<T> ptr) {
                _components[_lastIndex++] = ptr;

                if(_lastIndex >= _size)
                    throw std::exception("ECS_ComponentContainer near overflow");

                return ECS_Index<T>(_lastIndex - 1);
            }

            template<typename T>
            bool has() {
                for(auto i = 0; i < _lastIndex; ++i) {
                    if(dynamic_cast<T*>(_components[i].get()))
                        return true;
                }

                return false;
            }
    };
}

#endif