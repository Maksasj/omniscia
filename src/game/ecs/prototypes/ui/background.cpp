#include "background.h"

omniscia::core::Background::Background() : Entity() {
    add<ECS_SpriteRenderer>("menu_background", 0);
}

omniscia::core::Background::Background(const BackgroundProp& prop) : Entity() {
    add<ECS_SpriteRenderer>(prop._texture, prop._layer);
}
