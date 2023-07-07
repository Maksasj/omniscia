/**
 * @file 
 * ecs_sprite_animation.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_SPRITE_ANIMATION_H_
#define _ECS_SPRITE_ANIMATION_H_

#include <array>
#include <memory>
#include <iostream>

#include "animation_manager.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "animation.h"
#include "controls.h"
#include "entity.h"
#include "sprite.h"
#include "shader.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    /**
     * @brief ECS_SpriteAnimation - component that
     * manages sprite animations, updates animation frames
    */
    class ECS_SpriteAnimation : public ECS_Component {
        protected:
            Entity* _parent;

            /** @brief Current frame of the animation */
            u64 _currentFrame;

            /** @brief Animation id */
            std::string _animationId;
            
            /** @brief Tick of the animation */
            u32 _tick;

            /**
             * @brief Pointer to the animation asset data
            */
            Animation* animation;
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_SpriteAnimation>;

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            void reindex(void* parent) override {
                _parent = (Entity*) parent;
            }

            /**
             * @brief Default constructor of the ECS_SpriteAnimation component
             * 
             * @param animationId id of the animation
            */
            ECS_SpriteAnimation(const std::string &animationId);
            
            /**
             * @brief Sets animation by it id
             * 
             * @param animationId animation ud
            */
            void set_animation(const std::string &animationId);
            
            /**
             * @brief Get the animation object
             * 
             * @return std::string 
             */
            std::string get_animation() const;

            /**
             * @brief Reset animation to frame 0
            */
            void reset_animation();

            Entity* get_parent() {
                return _parent;
            }

            /**
             * @brief Get the frame size of the animation
             * 
             * @return Vec2f frame size 
            */
            Vec2f get_frame_size() const;
            
            /**
             * @brief Get the frame offset of the animation
             * 
             * @return Vec2f frame offset
            */
            Vec2f get_frame_offset() const;

            /**
             * @brief Updates animation frame, and offset
            */
            virtual void update();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteAnimation>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_SpriteAnimation>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_SpriteAnimation, _enabled, _currentFrame, _animationId, _tick);

namespace omniscia::core::ecs {
    /**
     * @brief ECS_SpriteAnimationSystem - System 
     * class used for managing all updates and data for
     * all active ECS_SpriteAnimation type components
    */
    class ECS_SpriteAnimationSystem : public ECS_System<ECS_SpriteAnimation> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_SpriteAnimationSystem() : ECS_System<ECS_SpriteAnimation>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_SpriteAnimationSystem(ECS_SpriteAnimationSystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */
            void operator=(ECS_SpriteAnimationSystem const&) = delete;

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                for(ECS_SpriteAnimation* comp : _components) {
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
                }
            }

            /**
             * @brief Get the singleton instance of the ECS_SpriteAnimationSystem system
             * 
             * @return Reference to singleton instance of the ECS_SpriteAnimationSystem system
            */
            static ECS_SpriteAnimationSystem& get_instance() {
                static ECS_SpriteAnimationSystem instance;
                return instance;
            }
    };
}

#endif