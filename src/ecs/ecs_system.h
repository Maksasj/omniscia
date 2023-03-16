#ifndef _ECS_SYSTEM_H_
#define _ECS_SYSTEM_H_

#include <memory>
#include <vector>

namespace omniscia::core::ecs {
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