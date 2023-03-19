#ifndef _ECS_PHYSICS_POSITIONED_H_
#define _ECS_PHYSICS_POSITIONED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_system.h" 
#include "ecs_component.tpp"

namespace omniscia::core::ecs {
    class ECS_PhysicsPositioned : public ECS_Component {
        /* Update and late update stuff */
        Vec3f _oldPosition;
        Vec3f _newPosition;
        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_PhysicsPositioned();

            Vec3f get_old_position() const;
            Vec3f get_new_position() const;
            void set_old_position(const Vec3f& value);
            void set_new_position(const Vec3f& value);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PhysicsPositioned>(*this));
            }
    };
}

#endif