#ifndef _ECS_COMPONENT_STATE_MACHINE_BASE_H_
#define _ECS_COMPONENT_STATE_MACHINE_BASE_H_

#include "ecs_system.h"
#include "ecs_component.tpp"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_StateMachineBase : public ECS_Component {
        private:
            void (ECS_StateMachineBase::*_activeState)();
        public:
            void time_sync() override;

            ECS_StateMachineBase();

            virtual void update();

            template<class T>
            void switch_state(void (T::*state)()) {
                using fptr = void (ECS_StateMachineBase::*)();
                _activeState = (fptr)state;   
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_StateMachineBase>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_StateMachineBase);
            }
    };

    class ECS_StateMachineBaseSystem : public ECS_System<ECS_StateMachineBase> {
        private:
            ECS_StateMachineBaseSystem() {};
            ECS_StateMachineBaseSystem(ECS_StateMachineBaseSystem const&) {};
            void operator=(ECS_StateMachineBaseSystem const&) {};
        public:
            void update() {
                // std::cout << _components.size() << "\n";
                for(ECS_StateMachineBase* comp : _components)
                    comp->update();
            }

            static ECS_StateMachineBaseSystem& get_instance() {
                static ECS_StateMachineBaseSystem instance;
                return instance;
            }
    };
}

#endif
