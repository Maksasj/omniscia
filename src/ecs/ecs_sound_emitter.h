/**
 * @file 
 * ecs_sound_emitter.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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

    /**
     * @brief ECS_SoundEmitter - component that used
     * for playing sound, provides acces to the
     * sound system for other entity components
    */
    class ECS_SoundEmitter : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief Sound speaker instance of this sound emitter */
            SoundSpeaker _speaker;

            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> _posIndex;

        public:
            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            void reindex(void* parent) override;

            /**
             * @brief Default constructor of the ECS_SoundEmitter component
            */
            ECS_SoundEmitter();

            /**
             * @brief Method used for updating sound speaker
            */
            void update();

            /**
             * @brief Try to play sound by it sound id
             * 
             * @param soundId id of the sound
            */
            void play(const std::string& soundId);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SoundEmitter>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_SoundEmitter);
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
