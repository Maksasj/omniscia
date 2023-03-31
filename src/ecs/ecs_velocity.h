#ifndef _ECS_COMPONENT_VELOCITY_H_
#define _ECS_COMPONENT_VELOCITY_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "types.tpp"
#include "entity.h"
 
namespace omniscia::core::ecs {
    class ECS_Velocity : public ECS_Component {
        private:
            Vec3f _vel;

            Vec2f _velocityRangesX;
            Vec2f _velocityRangesY;
        public:
            ECS_Velocity(const f32& velX = 0.0f, const f32& velY = 0.0f, const f32& velZ = 0.0f);
            ECS_Velocity(const Vec3f& vel, const Vec2f& velocityRangesX);
            ECS_Velocity(const Vec3f& vel, const Vec2f& velocityRangesX, const Vec2f& velocityRangesY);
            ECS_Velocity(const Vec2f& velocityRangesX, const Vec2f& velocityRangesY);

            void reindex(void* parent) override;

            Vec3f get_velocity() const;
            Vec3f& ref_velocity();
            void add_velocity(Vec3f force);
            void set_velocity(Vec3f velocity);

            void clamp_velocity() {
                if(_vel.x > _velocityRangesX.x) _vel.x = _velocityRangesX.x;
                if(_vel.y > _velocityRangesY.x) _vel.y = _velocityRangesY.x;
                //if(_vel.z > _maxVelocityZ) _vel.z = _maxVelocityZ;
                
                if(_vel.x < _velocityRangesX.y) _vel.x = _velocityRangesX.y;
                if(_vel.y < _velocityRangesY.y) _vel.y = _velocityRangesY.y;
                //if(_vel.z < _minVelocityZ) _vel.z = _minVelocityZ;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Velocity>(*this));
            }
    };
}

#endif