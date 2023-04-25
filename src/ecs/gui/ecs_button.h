/**
 * @file 
 * ecs_gravity.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_BUTTON_H_
#define _ECS_BUTTON_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs_box_collider_mesh.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_scaled.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"
#include "debug_ui.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_Button : public ECS_Component {
        private:
            Entity* _parent;

            std::function<void(ECS_Button&)> _clickLambda;
            std::function<void(ECS_Button&)> _hoverLambda;
            std::function<void(ECS_Button&)> _unHoverLambda;

            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            ECS_Index<ECS_BoxColliderMesh> _colliderIndex;

        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_Button(const std::function<void(ECS_Button&)> clickLambda);
            ECS_Button(const std::function<void(ECS_Button&)> clickLambda, const std::function<void(ECS_Button&)> hoverLambda, const std::function<void(ECS_Button&)> unHoverLambda);

            void update();

            Entity* get_parent() {
                return _parent;
            }

            ECS_Index<ECS_Positioned> get_pos_index() const {
                return _posIndex;
            }

            ECS_Index<ECS_Scaled> get_scale_index() const {
                return _scaleIndex;
            }

            ECS_Index<ECS_BoxColliderMesh> get_collider_index() const {
                return _colliderIndex;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Button>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Button);
            }
    };

    class ECS_ButtonSystem : public ECS_System<ECS_Button> {
        private:
            ECS_ButtonSystem() : ECS_System<ECS_Button>() {};
            ECS_ButtonSystem(ECS_ButtonSystem const&) {};
            void operator=(ECS_ButtonSystem const&) {};

        public:
            void update() {
                if(!_enabled)
                    return;

                for(ECS_Button* comp : _components) {
                    comp->update();

                    /* Resolve this cringe */
                    if(DebugUI::get_instance().get_metrics()._isTimeJump)
                            break;
                }
            }

            static ECS_ButtonSystem& get_instance() {
                static ECS_ButtonSystem instance;
                return instance;
            }
    };
}

#endif
