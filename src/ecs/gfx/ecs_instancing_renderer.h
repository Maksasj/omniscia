#ifndef _ECS_INSTANCING_RENDERER_H_
#define _ECS_INSTANCING_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_sprite_animation.h"
#include "ecs_pro_renderer.h"
#include "ecs_component.tpp"
#include "ecs_sprite_flip.h"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "instancing_sprite.h"
#include "shader.h"
#include "ecs_transparency.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_InstancingRenderer : public ECS_ProRenderer {
        protected:
            Entity* _parent;

            InstancingSprite _instancingSprite;
            //std::vector<InstancingData> _instancingData;
            InstancingData* _instancingData;
            i32 _instanceCount;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            ECS_Index<ECS_Transparency> _transparencyIndex;

        public:
            void time_sync() override;

            void reindex(void* parent) override;

            ECS_InstancingRenderer(const std::string& textureId, const i32& instanceCount, const u32& layer);

            ECS_InstancingRenderer(const ECS_InstancingRenderer& instance) :
                _instancingSprite(instance._instancingSprite),
                ECS_ProRenderer(RenderStagePool::get_instance().get_stage_by_name("MainStage"), instance.get_layer()) 
            {
                _parent = instance._parent;
                _instanceCount = instance._instanceCount;

                _instancingData = new InstancingData[instance._instanceCount];
                std::copy(instance._instancingData, instance._instancingData + instance._instanceCount, _instancingData);

                _spriteFlipIndex = instance._spriteFlipIndex;
                _animationIndex = instance._animationIndex;
                _posIndex = instance._posIndex;
                _scaleIndex = instance._scaleIndex;
                _transparencyIndex = instance._transparencyIndex;
            }

            ECS_InstancingRenderer& operator=(const ECS_InstancingRenderer& comp) {
                if(this == &comp)
                    return *this;

                if(_instanceCount != comp._instanceCount) {
                    InstancingData* tmp = new InstancingData[comp._instanceCount];
                    delete [] _instancingData;
                    _instancingData = tmp;
                    _instanceCount = comp._instanceCount;
                }

                std::copy(comp._instancingData, comp._instancingData + comp._instanceCount, _instancingData);

                return *this;
            }

            ~ECS_InstancingRenderer() {
                delete [] _instancingData;
            }

            void render() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_InstancingRenderer>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_InstancingRenderer);
            }
    };
}

#endif