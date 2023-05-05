/**
 * @file 
 * ecs_system.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_SYSTEM_H_
#define _ECS_SYSTEM_H_

#include <functional>
#include <memory>
#include <vector>

#include "types.tpp"

namespace omniscia::core::ecs {
    using namespace omni::types;

    /**
     * @brief Function used for sorting vector that is nearly sorted(Insertion sort)
     * 
     * @tparam T type of the elements that are stored in the vector
     * @param arr refernce to the vector instance
     * @param cmp comparison lambda expression used for comparing elements
    */
    template<typename T>
    void near_sorted_sort(std::vector<T>& arr, const std::function<bool(T, T)> cmp) {
        for(int i = 1; i < arr.size(); i++) {
            T key = arr[i];
            int j;
            for(j = i - 1; j >= 0 && cmp(arr[j], key); j--) {
                arr[j+1] = arr[j];
            }
            arr[j+1] = key;
        }
    };

    /**
     * @brief ECS_System - generic class used for 
     * declaring other components system, stores components, 
     * manages their life time, updates 
     * 
     * @tparam T type of the component that will be managed by this system instance
     */
    template<typename T>
    class ECS_System {
        protected:
            /** @brief Container of the active components */
            std::vector<T*> _components;

            /**
             * @brief Is system is enabled
            */
            bool _enabled;

            ECS_System() : _enabled(true) {}

        public:
            /** @brief Virtual method used for updating components (Optional)*/
            virtual void update() {}
            
            /** @brief Virtual method used for rendering components (Optional)*/
            virtual void render() {}

            /**
             * @brief Binds component to the active system
             * 
             * @param pointer to the component
            */
            virtual void bind_component(T* component) {
                _components.push_back(component);
            }

            /**
             * @brief Method that sort components by lambda expression
             * 
             * @param cmp lambda expression used for comparing different component
            */
            virtual void sort_components(const std::function<bool(const T*,const T*)> cmp) {
                near_sorted_sort<T*>(_components, cmp);
            }
            
            /** @brief Function that does time synchronisation */
            virtual void time_sync() {
                _components.clear();
            }

            /**
             * @brief Method used for getting singleton instance of the system
             * 
             * @return ECS_System<T>& reference to singleton instance of the system
            */
            static ECS_System<T>& get_instance() {
                static ECS_System<T> instance;
                return instance;
            }

            void enable() {
                _enabled = true;
            }

            void disable() {
                _enabled = false;
            }
    };
}

#endif