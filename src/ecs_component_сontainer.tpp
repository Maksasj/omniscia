#ifndef _ECS_COMPONENT_CONTAINER_H_
#define _ECS_COMPONENT_CONTAINER_H_

#include <vector>
#include <cassert>
#include <optional>

#include "ecs_component_сontainer_index.tpp"
#include "ecs_component.tpp"
#include "types.h"

namespace omniscia::core::ecs {
    class ECS_ComponentContainer {
        private:
            std::vector<std::shared_ptr<ECS_Component>> _components;
        public:
            ECS_ComponentContainer() {}

            ECS_ComponentContainer clone() const {
                ECS_ComponentContainer cont;
                
                for(auto &c : _components) {
                    cont._components.push_back(c->clone());
                }

                return cont;
            }

            /* Add and return index */
            template<typename T>
            ECS_Index<T> add_and_index(std::shared_ptr<T> component) {
                _components.push_back(component);
                return ECS_Index<T>(_components.size() - 1);
            }

            template<typename T>
            ECS_Index<T> add_and_index(const T& component) {
                _components.push_back(std::make_shared<T>(component));
                return ECS_Index<T>(_components.size() - 1);
            }

            /* Add */
            template<typename T>
            void add(std::shared_ptr<T> component) {
                _components.push_back(component);
            }

            template<typename T>
            void add(const T& component) {
                _components.push_back(std::make_shared<T>(component));
            }

            /* Get by type*/
            template<typename T>
            std::optional<std::shared_ptr<T>> get() const {
                for(auto &c : _components) {
                    auto ptr = std::dynamic_pointer_cast<T>(c);

                    if(ptr)
                        return ptr;
                }

                return std::nullopt;
            }

            template<typename T>
            std::shared_ptr<T> get_unsafe() const {
                for(auto &c : _components) {
                    auto std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(c);

                    if(ptr)
                        return ptr;
                }

                return std::make_shared<T>(NULL);
            }

            /* Reference component directly */
            /* By type */
            template<typename T>
            std::optional<std::reference_wrapper<T>> ref() const {
                for(auto &c : _components) {
                    std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(c);

                    if(ptr) {
                        return *ptr;
                    }
                }

                return std::nullopt;
            }

            template<typename T>
            T& ref_unsafe() const {
                for(auto &c : _components) {
                    std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(c);

                    if(ptr) {
                        return *ptr;
                    }
                }
                
                assert(false && "Tried unsafe ecs component reference, and failed");

                #pragma clang diagnostic push
                #pragma clang diagnostic ignored "-Wnull-dereference"
                return *((T*)nullptr);
                #pragma clang diagnostic pop
            }

            /* By index */
            template<typename T>
            std::optional<std::reference_wrapper<T>> ref(u32 index) const {
                if(index > _components.size()) return std::nullopt;
                return *std::dynamic_pointer_cast<T>(_components[index]);
            }

            template<typename T>
            T& ref_unsafe(u32 index) const {
                return *std::dynamic_pointer_cast<T>(_components[index]);
            }
            
            /* Index by index / get by index */
            template<typename T>
            std::optional<std::shared_ptr<T>> index(u32 index) const {
                if(index > _components.size()) return std::nullopt;

                auto pp = std::dynamic_pointer_cast<T>(_components[index]); 

                if(pp)
                    return pp;

                return std::nullopt;
            }

            template<typename T>
            std::shared_ptr<T> index_unsafe(u32 index) const {
                return std::dynamic_pointer_cast<T>(_components[index]);
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