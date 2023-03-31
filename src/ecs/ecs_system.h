#ifndef _ECS_SYSTEM_H_
#define _ECS_SYSTEM_H_

#include <functional>
#include <memory>
#include <vector>

namespace omniscia::core::ecs {
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

    template<typename T>
    class ECS_System {
        protected:
            std::vector<T*> _components;
        public:
            virtual void update() {}
            virtual void render() {}

            void bind_component(T* component) {
                _components.push_back(component);
            }

            void sort_components(const std::function<bool(const T*,const T*)> cmp) {
                near_sorted_sort<T*>(_components, cmp);
            }
            
            void time_sync() {
                _components.clear();
            }

            static ECS_System<T>& get_instance() {
                static ECS_System<T> instance;
                return instance;
            }
    };
}

#endif