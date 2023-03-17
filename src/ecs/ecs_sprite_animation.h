#ifndef _ECS_SPRITE_ANIMATION_H_
#define _ECS_SPRITE_ANIMATION_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_system.h" 

#include "sprite.h"
#include "shader.h"
#include "ecs_component.tpp"
#include "controls.h"
#include "ecs_positioned.h"
#include "ecs_scaled.h"

namespace omniscia::core::ecs {
    using namespace omniscia::renderer::sprite;
    using namespace omniscia::renderer; 

    class ECS_SpriteAnimation : public ECS_Component {
        private:
            u64 _currentFrame;

            Vec2f _spriteUvSize; // 1.0, 1.0
            Vec2f _spriteFrameSize; //0.0 - 1.0
            Vec2f _startPossition;

            u64 _frameCount;
            bool _direction;        //Horizontal | Vertical

            u64 _animationSpeed;
        public:
            void time_sync() override;

            ECS_SpriteAnimation(const Vec2f& spriteUvSize,const Vec2f& spriteFrameSize, const Vec2f& startPossition, const u32& frameCount,const bool& direction);

            Vec2f get_frame_size() const {
                return _spriteFrameSize;
            }

            Vec2f get_frame_offset() const {
                if(_direction)
                    return Vec2f{_startPossition.x + _currentFrame*_spriteFrameSize.x, _startPossition.y};

                return Vec2f{_startPossition.x, _startPossition.y + _spriteFrameSize.y*_currentFrame};
            }

            void update() {
                static u64 tick = 0;
                ++tick;

                if(tick % 120 == 0) {
                    ++_currentFrame;

                    if(_currentFrame >= _frameCount) {
                        _currentFrame = 0;
                    }
                }
            };

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteAnimation>(*this));
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