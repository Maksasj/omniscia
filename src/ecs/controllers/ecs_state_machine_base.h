/**
 * @file 
 * ecs_state_machine_base.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_STATE_MACHINE_BASE_H_
#define _ECS_COMPONENT_STATE_MACHINE_BASE_H_

#include "ecs_system.h"
#include "ecs_component.tpp"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_StateMachineBase - base component
     * that used by other ai components, used as
     * state machine, for now used only by crab ai 
    */
    class ECS_StateMachineBase : public ECS_Component {
        protected:
            Entity *_parent;

        private:
            /**
             * @brief Pointer to the member function that represents
             * active state machine state
            */
            void (ECS_StateMachineBase::*_activeState)();
            
        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_StateMachineBase, ""); 
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_StateMachineBase, ""); 

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            void reindex(void* parent) override;

            Entity* get_parent() {
                return _parent;
            }

            /**
             * @brief Default constructor of the ECS_StateMachineBase component
            */
            ECS_StateMachineBase();

            /**
             * @brief Virtual method used for other ECS_StateMachineBase based
             * ai components 
            */
            virtual void update();

            /**
             * @brief Switches active state of the state machine
             * 
             * @tparam T type of the inherited state machine
             * @param state pointer to the state method
            */
            template<class T>
            void switch_state(void (T::*state)()) {
                using fptr = void (ECS_StateMachineBase::*)();
                _activeState = (fptr)state;   
            }

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_StateMachineBase>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_StateMachineBase);
            }
    };

    /**
     * @brief ECS_StateMachineBaseSystem - System 
     * class used for managing all updates and data for
     * all active ECS_StateMachineBase type components
    */
    class ECS_StateMachineBaseSystem : public ECS_System<ECS_StateMachineBase> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_StateMachineBaseSystem() : ECS_System<ECS_StateMachineBase>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_StateMachineBaseSystem(ECS_StateMachineBaseSystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */
            void operator=(ECS_StateMachineBaseSystem const&) = delete;

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                for(ECS_StateMachineBase* comp : _components) {
                    if(comp == nullptr)
                        continue;

                    Entity* parent = comp->get_parent();

                    if(DebugUI::get_instance().get_metrics()._isTimeJump) {
                        if(parent == nullptr)
                            continue;
                        
                        const EntityTimeType timeType = parent->get_time_type();
                        
                        if(timeType == EntityTimeType::STATIC)
                            comp->update();
                    } else {
                        comp->update();
                    }
                }
            }

            /**
             * @brief Get the singleton instance of the ECS_StateMachineBaseSystem system
             * 
             * @return Reference to singleton instance of the ECS_StateMachineBaseSystem system
            */
            static ECS_StateMachineBaseSystem& get_instance() {
                static ECS_StateMachineBaseSystem instance;
                return instance;
            }
    };
}

#endif
