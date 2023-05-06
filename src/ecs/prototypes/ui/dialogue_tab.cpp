#include "dialogue_tab.h"

omniscia::core::DialogueTab::DialogueTab(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Scaled>(0.2f, 0.2f);
    add<ECS_Transparency>(0.0f);
    add<ECS_SpriteRenderer>("dialogue", 10);
}
