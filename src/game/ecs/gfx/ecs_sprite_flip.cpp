#include "ecs/gfx/ecs_sprite_flip.h"

omniscia::core::ecs::ECS_SpriteFlip::ECS_SpriteFlip() {
    _horizontalFlip = false;
    _verticalFlip = false;
}

omniscia::core::ecs::ECS_SpriteFlip::ECS_SpriteFlip(const bool& horizontalFlip, const bool& verticalFlip) {
    _horizontalFlip = horizontalFlip;
    _verticalFlip = verticalFlip;
}

bool omniscia::core::ecs::ECS_SpriteFlip::get_horizontal_flip() const {
    return _horizontalFlip;
}

bool omniscia::core::ecs::ECS_SpriteFlip::get_vertical_flip() const {
    return _verticalFlip;
}

void omniscia::core::ecs::ECS_SpriteFlip::set_horizontal_flip(const bool& flip) {
    _horizontalFlip = flip;
}

void omniscia::core::ecs::ECS_SpriteFlip::set_vertical_flip(const bool& flip) {
    _verticalFlip = flip;
}
