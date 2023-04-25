#include "background.h"

omniscia::core::Background::Background() {
    add<ECS_SpriteRenderer>("menu_background", 0);
}

omniscia::core::Background::Background(const BackgroundProp& prop) {
    add<ECS_SpriteRenderer>(prop._texture, prop._layer);
}
