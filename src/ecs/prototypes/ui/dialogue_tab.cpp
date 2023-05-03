#include "dialogue_tab.h"

omniscia::core::DialogueTab::DialogueTab(const Vec2f& pos) : Entity() {
    add<ECS_Positioned>(pos.x, pos.y);
    add<ECS_Scaled>(0.2f, 0.2f);
    add<ECS_Transparency>(0.0f);
    add<ECS_SpriteRenderer>("dialogue", 10);
}
