#ifndef _ECS_PRO_RENDERER_H_
#define _ECS_PRO_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs/gfx/ecs_sprite_animation.h"
#include "ecs/ecs_component.tpp"
#include "ecs/gfx/ecs_sprite_flip.h"
#include "ecs/motion/ecs_positioned.h"
#include "ecs/ecs_system.h"
#include "ecs/motion/ecs_scaled.h"
#include "controls.h"
#include "ecs/entity.h"
#include "gfx/sprite.h"
#include "gfx/shader.h"
#include "gfx/render_stage_pool.h"
#include "ecs/gfx/ecs_transparency.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_ProRenderer : public ECS_Component {
        protected:
            RenderStage* _bindedRenderingStage;

            u32 _layer;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_ProRenderer>;

            ECS_ProRenderer(RenderStage* renderingStage, const u32& layer);

            RenderStage* get_rendering_stage() const; 

            u32 get_layer() const;

            virtual void render() {};

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_ProRenderer>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_ProRenderer, _enabled, _layer);

namespace omniscia::core::ecs {
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