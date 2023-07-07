#ifndef _COLLECTED_TEXT_H_
#define _COLLECTED_TEXT_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CollectedTextProp {
        std::string _fontId = "";
        std::string _textToRender = "";
        f32 _lineLetterSpacing = 1.0f;
        f32 _rowLineSpacing = 1.0f;
        u64 _charactersPerRow = 8u;
    };

    class CollectedText : public Entity {
        private:

        public:
            CollectedText(const CollectedTextProp& prop);
            CollectedText(const Vec2f& position, const Vec2f& scale, const CollectedTextProp& prop);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<CollectedText> entity = std::make_shared<CollectedText>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
