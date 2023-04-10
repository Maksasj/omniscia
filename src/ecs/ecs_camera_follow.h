#ifndef _ECS_COMPONENT_CAMERA_FOLLOW_H_
#define _ECS_COMPONENT_CAMERA_FOLLOW_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_sprite_animation.h"
#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_sprite_flip.h"
#include "ecs_velocity.h"
#include "ecs_system.h"
#include "timesystem.h"
#include "controls.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_CameraFollow : public ECS_Component {
        private:
            Entity* _parent;

            Vec3f _camPos;
            f32 _cameraFollowSpeed;

            ECS_Index<ECS_Positioned> posIndex;
        public:
            void reindex(void* parent) override;
            void time_sync() override;

            ECS_CameraFollow(const f32& cameraFollowSpeed = 0.005f);

            void update(Shader* shader);

            Vec3f get_camera_pos() const;
            Vec3f& ref_camera_pos();
            f32 get_camera_follow_speed() const;
            f32& ref_camera_follow_speed();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_CameraFollow>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_CameraFollow);
            }
    };

    class ECS_CameraFollowSystem : public ECS_System<ECS_CameraFollow> {
        private:
            ECS_CameraFollowSystem() {};
            ECS_CameraFollowSystem(ECS_CameraFollowSystem const&) {};
            void operator=(ECS_CameraFollowSystem const&) {};
        public:
            void update(Shader* shader) {
                for(ECS_CameraFollow* comp : _components) {
                    comp->update(shader);
                }
            }

            static ECS_CameraFollowSystem& get_instance() {
                static ECS_CameraFollowSystem instance;
                return instance;
            }
    };
}

#endif
