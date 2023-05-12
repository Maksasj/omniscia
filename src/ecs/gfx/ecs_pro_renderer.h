#ifndef _ECS_PRO_RENDERER_H_
#define _ECS_PRO_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_sprite_animation.h"
#include "ecs_component.tpp"
#include "ecs_sprite_flip.h"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "sprite.h"
#include "shader.h"
#include "render_stage_pool.h"
#include "ecs_transparency.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_ProRenderer : public ECS_Component {
        protected:
            RenderStage* _bindedRenderingStage;

            u32 _layer;

        public:
            ECS_ProRenderer(RenderStage* renderingStage, const u32& layer);

            RenderStage* get_rendering_stage() const; 

            u32 get_layer() const;

            virtual void render() {};
    };

    struct Predicate_ProRendereLayerTop {
        bool operator()(const ECS_ProRenderer* first, const ECS_ProRenderer* second) {
            return first->get_layer() > second->get_layer();
        }
    }; 

    struct Predicate_ProRendereLayerBottom {
        bool operator()(const ECS_ProRenderer* first, const ECS_ProRenderer* second) {
            return first->get_layer() > second->get_layer();
        }
    };

    class ECS_ProRendererSystem : public ECS_System<ECS_ProRenderer> {
        private:
            std::vector<std::vector<ECS_ProRenderer*>> _proComponents;

            ECS_ProRendererSystem() : _proComponents(RenderStagePool::get_instance().rendering_stage_count()), ECS_System<ECS_ProRenderer>() {

            };

            ECS_ProRendererSystem(ECS_ProRendererSystem const&) {};
            void operator=(ECS_ProRendererSystem const&) {};

        public:
            void render() override {

                if(!_enabled)
                    return;

                RenderStage* activeStage = RenderStage::get_active_render_stage();

                if(activeStage == nullptr) 
                    return;

                auto& components = _proComponents[activeStage->get_stage_id()];
                
                std::for_each(components.begin(), components.end(), [&](ECS_ProRenderer* comp) {
                    comp->render();
                });
            }

            void bind_component(ECS_ProRenderer* component) override {
                auto bindedRenderingStage = component->get_rendering_stage();

                if(bindedRenderingStage == nullptr)
                    return;

                auto& components = _proComponents[bindedRenderingStage->get_stage_id()];

                components.push_back(component);

                system_sort<ECS_ProRenderer*>(components, Predicate_ProRendereLayerTop());
            }

            void time_sync() override {
                std::for_each(_proComponents.begin(), _proComponents.end(), [&](std::vector<omniscia::core::ecs::ECS_ProRenderer*>& components) {
                    components.clear();
                });
            }

            static ECS_ProRendererSystem& get_instance() {
                static ECS_ProRendererSystem instance;
                return instance;
            }
    };
}

#endif