#ifndef _ECS_COMPONENT_INTERACTIVE_H_
#define _ECS_COMPONENT_INTERACTIVE_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_trigger_aabb_collider.h"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"
#include "debug_info.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_Interactive : public ECS_Component {
        protected:
            Entity* _parent;

            std::function<void(void)> _lambda;
            f32 _cooldown;
            f32 _timer;

            ECS_Index<ECS_TriggerAABBCollider> _triggerColliderIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Interactive>;

            void time_sync() override;
            void reindex(void* parent) override;

            ECS_Interactive(const f32& cooldown, const std::function<void(void)>& lambda);

            virtual void update() {};

            Entity* get_parent() {
                return _parent;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Interactive>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Interactive>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Interactive, _enabled, _cooldown, _timer);

namespace omniscia::core::ecs {
    class ECS_InteractiveSystem : public ECS_System<ECS_Interactive> {
        private:
            ECS_InteractiveSystem() : ECS_System<ECS_Interactive>() {};
            ECS_InteractiveSystem(ECS_InteractiveSystem const&) {};
            void operator=(ECS_InteractiveSystem const&) {};

        public:
            void update() {
                if(!_enabled)
                    return;

                for(ECS_Interactive* comp : _components) {
                    if(comp == nullptr)
                        continue;

                    Entity* parent = comp->get_parent();

                    if(DebugInfo::get_instance().get_metrics()._isTimeJump) {
                        if(parent == nullptr)
                            continue;
                        
                        const EntityTimeType timeType = parent->get_time_type();
                        
                        if(timeType == EntityTimeType::STATIC)
                            comp->update();
                    } else {
                        comp->update();
                    }
                    

                    if(DebugInfo::get_instance().get_metrics()._systemInterupt) {
                        DebugInfo::get_instance().get_metrics()._systemInterupt = false;
                        return;
                    }
                }
            }

            static ECS_InteractiveSystem& get_instance() {
                static ECS_InteractiveSystem instance;
                return instance;
            }
    };
}

#endif
