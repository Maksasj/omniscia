#ifndef _ECS_COMPONENT_VELOCITY_H_
#define _ECS_COMPONENT_VELOCITY_H_

#include <array>
#include <memory>
#include <iostream>

#include "types.tpp"
#include "ecs_component.tpp"
#include "entity.h"
#include "controls.h"

namespace omniscia::core::ecs {
    class ECS_Velocity : public ECS_Component {
        private:
            Vec3f _vel;
            f32 _maxVelocity;
            f32 _minVelocity;
        public:
            ECS_Velocity();
            ECS_Velocity(const Vec3f& vel);
            ECS_Velocity(const Vec3f& vel, const f32& maxVelocity);
            ECS_Velocity(const Vec3f& vel, const f32& maxVelocity, const f32& minVelocity);
            ECS_Velocity(const f32& maxVelocity, const f32& minVelocity);

            void reindex(void* parent) override;

            Vec3f get_velocity() const;
            Vec3f& ref_velocity();
            void add_velocity(Vec3f force);
            void set_velocity(Vec3f velocity);

            void clamp_velocity() {
                if(_vel.x > _maxVelocity) _vel.x = _maxVelocity;
                if(_vel.y > _maxVelocity) _vel.y = _maxVelocity;
                if(_vel.z > _maxVelocity) _vel.z = _maxVelocity;
                
                if(_vel.x < _minVelocity) _vel.x = _minVelocity;
                if(_vel.y < _minVelocity) _vel.y = _minVelocity;
                if(_vel.z < _minVelocity) _vel.z = _minVelocity;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Velocity>(*this));
            }
    };
}

#endif