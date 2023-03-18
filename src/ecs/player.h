#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

#include "ecs_player_controller.h"
#include "ecs_sprite_renderer.h"
#include "ecs_sprite_animation.h"
#include "ecs_2d_physics_rigidbody.h"
#include "ecs_spritesheet_renderer.h"
#include "ecs_scaled.h"
#include "ecs_positioned.h"
#include "ecs_aabb_collider.h"
#include "ecs_velocity.h"
#include "ecs_movable_aabb_collider.h"
#include "ecs_gravity.h"
#include "ecs_velocity_slowdown.h"
#include "ecs_sprite_flip.h"

namespace omniscia::core {
    class Player : public Entity {
        public:
            Player() {
                add(new ECS_Positioned({0.0f, 1.0f}));
                ///add(new ECS_Velocity(0.1f, 0.1f));
                add(new ECS_Velocity(0.1f, -0.1f));
                add(new ECS_Scaled({0.25f, 0.25f}));
                
                add(new ECS_SpriteFlip(false, false));
                add(new ECS_SpriteAnimation("player-run-animation"));
                add(new ECS_SpriteSheetRenderer("player-spritesheet", *this, 1));
                
                //add(new ECS_Gravity(*this));
                add(new ECS_VelocitySlowdown(*this));
                
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
