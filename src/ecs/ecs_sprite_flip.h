#ifndef _ECS_COMPONENT_SPRITE_FLIP_H_
#define _ECS_COMPONENT_SPRITE_FLIP_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    class ECS_SpriteFlip : public ECS_Component {
        private:
            bool _horizontalFlip;
            bool _verticalFlip;
        public:
            void reindex(void* parent) override;
            
            ECS_SpriteFlip();
            ECS_SpriteFlip(const bool& horizontalFlip, const bool& verticalFlip);

            bool get_horizontal_flip() const;
            bool get_vertical_flip() const;
            void set_horizontal_flip(const bool& flip);
            void set_vertical_flip(const bool& flip);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteFlip>(*this));
            }
    };
}

#endif