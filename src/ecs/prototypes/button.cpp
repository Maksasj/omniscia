#include "button.h"

omniscia::core::Button::Button() {
    add<ECS_Positioned>(0.0f, 0.0f);
    add<ECS_Scaled>(0.1f, 0.1f);
    add<ECS_BoxColliderMesh>(Vec2f{1.0f, 1.0f}, Vec2f{1.0f, 1.0f});
    add<ECS_SpriteRenderer>("factorio_girl_texture", 0);
    add<ECS_Button>([]() {}, []() {});
}

omniscia::core::Button::Button(const std::function<void(void)> clickLambda, const std::function<void(void)> hoverLambda) {
    add<ECS_Positioned>(0.0f, 0.0f);
    add<ECS_Scaled>(0.1f, 0.1f);
    add<ECS_BoxColliderMesh>(Vec2f{1.0f, 1.0f}, Vec2f{1.0f, 1.0f});
    add<ECS_SpriteRenderer>("factorio_girl_texture", 0);
    add<ECS_Button>(clickLambda, hoverLambda);
}

omniscia::core::Button omniscia::core::Button::clone() {
    Button tmpButton = *this;
    clone_container_to(tmpButton);
    return tmpButton;
}
