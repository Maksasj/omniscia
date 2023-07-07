#include "ecs/prototypes/ui/dialogue_tab.h"

omniscia::core::DialogueTab::DialogueTab(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Scaled>(0.3f, 0.3f);
    add<ECS_Transparency>(0.0f);
    add<ECS_GuiSpriteRenderer>("dialogue", 10);
}
