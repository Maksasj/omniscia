#ifndef _ECS_COMPONENT_SOUND_EMITTER_H_
#define _ECS_COMPONENT_SOUND_EMITTER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_system.h"
#include "ecs_positioned.h"
#include "entity.h"
#include "ecs_component.tpp"

#include "sound_speaker.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_SoundEmitter : public ECS_Component {
        private:
            Entity* _parent;

            SoundSpeaker _speaker;

            ECS_Index<ECS_Positioned> _posIndex;
        public:
            void reindex(void* parent) override;
            void time_sync() override;

            ECS_SoundEmitter();

            void update();

            void play(const std::string& sound_id);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SoundEmitter>(*this));
            }
    };

    class ECS_SoundEmitterSystem : public ECS_System<ECS_SoundEmitter> {
        private:
            ECS_SoundEmitterSystem() {};
            ECS_SoundEmitterSystem(ECS_SoundEmitterSystem const&) {};
            void operator=(ECS_SoundEmitterSystem const&) {};
        public:
            void update() {
                for(ECS_SoundEmitter* comp : _components) {
                    comp->update();
                }
            }

            static ECS_SoundEmitterSystem& get_instance() {
                static ECS_SoundEmitterSystem instance;
                return instance;
            }
    };
}

#endif
