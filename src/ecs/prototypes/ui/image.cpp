#include "image.h"

omniscia::core::Image::Image(const ImageProp& prop) : Entity() {
    add<ECS_Positioned>(prop._pos.x, prop._pos.y);
    add<ECS_Scaled>(prop._scale.x, prop._scale.y);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_Transparency>(0.0f);
    add<ECS_GuiSpriteRenderer>(prop._texture, prop._layer);
}
