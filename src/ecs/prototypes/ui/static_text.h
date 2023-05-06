#ifndef _STATIC_TEXT_H_
#define _STATIC_TEXT_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct StaticTextProp {
        std::string _fontId = "";
        std::string _textToRender = "";
        f32 _lineLetterSpacing = 1.0f;
        f32 _rowLineSpacing = 1.0f;
        u64 _charactersPerRow = 8u;
    };

    class StaticText : public Entity {
        private:

        public:
            StaticText(const StaticTextProp& prop);
            StaticText(const Vec2f& position, const Vec2f& scale, const StaticTextProp& prop);

            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
