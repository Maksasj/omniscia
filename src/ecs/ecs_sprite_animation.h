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
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx; 

    class ECS_SpriteAnimation : public ECS_Component {
        private:
            u64 _currentFrame;
            std::string _animationId;
            
            u64 _tick;

            Animation* animation;
        public:
            void time_sync() override;

            ECS_SpriteAnimation(const std::string &animationId);
            
            void set_animation(const std::string &animationId);
            std::string get_animation() const;
            void reset_animation();
            
            Vec2f get_frame_size() const;
            Vec2f get_frame_offset() const;

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteAnimation>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_SpriteAnimation);
            }
    };

    class ECS_SpriteAnimationSystem : public ECS_System<ECS_SpriteAnimation> {
        private:
            ECS_SpriteAnimationSystem() {};
            ECS_SpriteAnimationSystem(ECS_SpriteAnimationSystem const&) {};
            void operator=(ECS_SpriteAnimationSystem const&) {};
        public:
            void update() {
                for(ECS_SpriteAnimation* comp : _components) {
                    comp->update();
                }
            }

            static ECS_SpriteAnimationSystem& get_instance() {
                static ECS_SpriteAnimationSystem instance;
                return instance;
            }
    };
}

#endif