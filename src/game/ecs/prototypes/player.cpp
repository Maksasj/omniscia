#include "player.h"

omniscia::core::Player::Player(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(0.2f, 0.2f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimationAuto>("player-idle-animation");
    add<ECS_SpriteSheetRenderer>("player-spritesheet", 1);
    // add<ECS_Gravity>();
    add<ECS_CameraFollow>(0.005f);
    add<ECS_PlayerController>();

    add<ECS_PlayerTimeJumpController>();
    add<ECS_PlayerCollectorController>();
    
    add<ECS_PlayerDebugMetrics>();
    add<ECS_PlayerJump>();
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{1.0f, 0.5f});
    add<ECS_MovableAABBCollider>(CollisionMask_Player, CollisionMask_Tiles);
    add<ECS_2DPhysicsRigidbody>();
}