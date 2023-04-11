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

namespace omniscia::core::ecs {
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

            /** @brief Current position of the camera */
            Vec3f _camPos;
            
            /** @brief Camera follow speed */
            f32 _cameraFollowSpeed;

            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> posIndex;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_CameraFollow, this->_parent << " " << this->_camPos << " " << this->_cameraFollowSpeed);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_CameraFollow, self._parent << " " << self._camPos << " " << self._cameraFollowSpeed);

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
            void update(Shader* shader);

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

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_CameraFollow);
            }
    };

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
            ECS_CameraFollowSystem() {};
            
            /**
             * @brief Hidden default copy constructor
            */
            ECS_CameraFollowSystem(ECS_CameraFollowSystem const&) {};
            
            /**
             * @brief Hidden default assignment operator
            */
            void operator=(ECS_CameraFollowSystem const&) {};

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update(Shader* shader) {
                for(ECS_CameraFollow* comp : _components) {
                    comp->update(shader);
                }
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
