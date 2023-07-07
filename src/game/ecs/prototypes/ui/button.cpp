#include "button.h"

omniscia::core::Button::Button(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Scaled>(0.1f, 0.1f);
    add<ECS_BoxColliderMesh>(Vec2f{1.0f, 1.0f}, Vec2f{1.0f, 1.0f});
    add<ECS_GuiSpriteRenderer>("new_game_button", 11);
    add<ECS_Button>([](ECS_Button&) {}, [](ECS_Button&) {}, [](ECS_Button&) {});
}

omniscia::core::Button::Button(const ButtonProp& prop) : Entity() {
    add<ECS_Positioned>(prop._pos.x, prop._pos.y);
    add<ECS_Scaled>(prop._scale.x, prop._scale.y);
    add<ECS_BoxColliderMesh>(prop._collider._xRanges, prop._collider._yRanges);
    add<ECS_GuiSpriteRenderer>(prop._renderer._texture, prop._renderer._layer);
    add<ECS_Button>(prop._clickLambda, prop._hoverLambda, prop._unHoverLambda);
}

omniscia::core::Button::Button(const Vec2f& position, const std::function<void(ECS_Button&)> clickLambda, const std::function<void(ECS_Button&)> hoverLambda) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Scaled>(0.1f, 0.1f);
    add<ECS_BoxColliderMesh>(Vec2f{1.0f, 1.0f}, Vec2f{1.0f, 1.0f});
    add<ECS_GuiSpriteRenderer>("new_game_button", 11);
    add<ECS_Button>(clickLambda, hoverLambda, [](ECS_Button&) {});
}
