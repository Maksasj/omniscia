/**
 * @file 
 * ecs_camera_follow.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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
#include "camera.h"
#include "debug_info.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_CameraFollow - component that manages,
     * smooth camera movement, camera will folow entity to
     * which it was assigned
    */
    class ECS_CameraFollow : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief Camera follow speed */
            f32 _cameraFollowSpeed;

            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> posIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_CameraFollow>;

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            void reindex(void* parent) override;

            /**
             * @brief Constructs a new ECS_CameraFollow object
             * 
             * @param cameraFollowSpeed the speed of camera follow
            */
            ECS_CameraFollow(const f32& cameraFollowSpeed = 0.005f);

            /**
             * @brief Method used for updating 
             * component, does some calculations
             * updates all uniforms
             * 
             * @param shader used for updating shader uniforms
            */
            void update();

            /**
             * @brief Get the camera position
             * 
             * @return the camera position
            */
            Vec3f get_camera_pos() const;

            /**
             * @brief Get a reference to the camera position
             * 
             * @return reference to the camera position
            */
            Vec3f& ref_camera_pos();

            /**
             * @brief Get the camera follow speed
             * 
             * @return the camera follow speed
            */
            f32 get_camera_follow_speed() const;

            /**
             * @brief Get a reference to the camera follow speed
             * 
             * @return reference to the camera follow speed
            */
            f32& ref_camera_follow_speed();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_CameraFollow>(*this));
            }

            Entity* get_parent() {
                return _parent;
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_CameraFollow>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_CameraFollow, _enabled, _cameraFollowSpeed);

namespace omniscia::core::ecs {
    /**
     * @brief ECS_CameraFollowSystem - System 
     * class used for managing all updates and data for
     * all active ECS_CameraFollow type components
    */
    class ECS_CameraFollowSystem : public ECS_System<ECS_CameraFollow> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_CameraFollowSystem() : ECS_System<ECS_CameraFollow>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_CameraFollowSystem(ECS_CameraFollowSystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */
            void operator=(ECS_CameraFollowSystem const&) = delete;

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                std::for_each(_components.begin(), _components.end(), [&](ECS_CameraFollow* comp) {
                    comp->update();
                });
            }

            /**
             * @brief Get the singleton instance of the ECS_CameraFollowSystem system
             * 
             * @return Reference to singleton instance of the ECS_CameraFollowSystem system
            */
            static ECS_CameraFollowSystem& get_instance() {
                static ECS_CameraFollowSystem instance;
                return instance;
            }
    };
}

#endif