#include "player.h"

omniscia::core::Player::Player() {
    add<ECS_Positioned>(Vec3f{0.0f, 0.0f});
    add<ECS_Velocity>(Vec2f{0.002f, -0.002f}, Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(Vec2f{0.2f, 0.2f});
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimation>("player-idle-animation");
    add<ECS_SpriteSheetRenderer>("player-spritesheet", 1);
    add<ECS_Gravity>();
    add<ECS_CameraFollow>(0.005f);
    add<ECS_PlayerController>();
    add<ECS_PlayerDebugMetrics>();
    add<ECS_PlayerJump>();
    add<ECS_MovableAABBCollider>();
    add<ECS_2DPhysicsRigidbody>();
}

omniscia::core::Player omniscia::core::Player::clone() {
    Player tmpPlayer = *this;
    clone_container_to(tmpPlayer);
    return tmpPlayer;
}
