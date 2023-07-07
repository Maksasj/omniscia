/**
 * @file 
 * ecs_component_container.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_CONTAINER_H_
#define _ECS_COMPONENT_CONTAINER_H_

#include <vector>
#include <cassert>
#include <optional>
#include <typeinfo>

#include "debug_scene_manager_window.h"

#include "ecs_component_container_index.tpp"
#include "ecs_component.tpp"
#include "omni_types.tpp"

namespace omniscia::core::ecs {
    using namespace omniscia::core;
    using namespace omni::types;
    
    /**
     * @brief ECS_ComponentContainer - class that stores pointer to
     * components, manges their life time, clonning, referencing
     * indexing and etc.
    */
    class ECS_ComponentContainer {
        private:
            std::vector<std::shared_ptr<ECS_Component>> _components;

        public:
            friend class ::omniscia::core::DebugSceneManagerWindow;

            /**
             * @brief Method used for clonning ECS_ComponentContainer 
             * cotainer, also clones all components inside it
             * 
             * @return new instance of the ECS_ComponentContainer 
            */
            ECS_ComponentContainer clone() const {
                ECS_ComponentContainer cont;

                for(auto &c : _components)
                    cont._components.push_back(c->clone());

                return cont;
            }

            /**
             * @brief References component by it ecs index
             * function unsafe, so use it for it own risk 
             * 
             * @tparam T type of the component 
             * @param index ecs index of the component
             * @return T& reference to the component
            */
            template<typename T>
            T& ref_unsafe(u32 index) const {
                return *std::dynamic_pointer_cast<T>(_components[index]);
            }

            /**
             * @brief Method that creates component inside 
             * component container and runs other initializations
             * 
             * @tparam T type of the component
             * @param parent pointer to the parent entity instane
            */
            template<class T>
            void add(void* parent) {
                std::shared_ptr<T> ptr(new T());
                ptr->reindex(parent);

                _components.push_back(ptr);
            }

            /**
             * @brief Method that creates component inside 
             * component container and runs other initializations
             * 
             * @tparam T type of the component
             * @tparam Args types of the arguments for the component
             * @param parent pointer to the parent entity instane
             * @param args arguments of the component constructor
            */
            template<class T, class... Args>
            void add(void* parent, Args&&... args) {
                std::shared_ptr<T> ptr(new T(std::forward<Args>(args)...));
                ptr->reindex(parent);

                _components.push_back(ptr);
            }

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds components to the
             * systems
            */
            void time_sync(void* parent) {
                for(auto &c : _components) {
                    c->reindex(parent);
                    c->time_sync();
                }
            }

            /**
             * @brief Method used for indexing 
             * component of the specific type
             * 
             * @tparam T type of the component that need to be searched 
             * @return ECS_Index<T> index of the component, 
             * if it was found, or failed if not
            */
            template<typename T>
            ECS_Index<T> index() const {
                for(u32 i = 0; i < _components.size(); ++i)
                    if(std::dynamic_pointer_cast<T>(_components[i]))
                        return ECS_Index<T>(i);

                return ECS_Index<T>(nullptr);
            }

            /**
             * @brief Checks if component of the specific type exist inside component container
             * 
             * @return True - component exist 
             * @return False - component does not exist
            */
            template<typename T> /* Utils */
            bool has() const {
                for(auto &c : _components)
                    if(std::dynamic_pointer_cast<T>(c))
                        return true;

                return false;
            }
            
            /**
             * @brief Returns amount of the components stored inside component container
             * 
             * @return u32 - amount of the components
            */
            u32 size() const {
                return _components.size();
            }
    };
}

#endif