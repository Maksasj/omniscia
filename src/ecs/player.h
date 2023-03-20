#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
#include "ecs_components.h"

namespace omniscia::core {
    class Player : public Entity {
        public:
            Player() {
                //add(new ECS_Positioned({0.0f, 1.0f}));
                add(new ECS_Positioned({0.0f, 0.0f}));
                add(new ECS_Velocity(0.003f, -0.003f));
                add(new ECS_PhysicsPositioned());
                add(new ECS_Acceleration());
                add(new ECS_Friction(-0.01));
                
                add(new ECS_Scaled({0.2f, 0.2f}));
                
                add(new ECS_SpriteFlip(false, false));
                add(new ECS_SpriteAnimation("player-idle-animation"));
                add(new ECS_SpriteSheetRenderer("player-spritesheet", *this, 1));
                
                add(new ECS_Gravity(*this));

                add(new ECS_CameraFollow(0.005f, *this));
                //add(new ECS_VelocitySlowdown(*this));
                
                add(new ECS_PlayerController(*this));
                add(new ECS_MovableAABBCollider(*this));
                add(new ECS_2DPhysicsRigidbody(*this));
            }

            Player clone() {
                Player tmpPlayer = *this;
                clone_container_to(tmpPlayer);
                return tmpPlayer;
            }
    };
}

#endif
