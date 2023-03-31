#ifndef _ECS_COMPONENT_ACCELERATION_H_
#define _ECS_COMPONENT_ACCELERATION_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "types.tpp"
#include "entity.h"

namespace omniscia::core::ecs {
    class ECS_Acceleration : public ECS_Component {
        private:
            Vec3f _acl;
        public:
            void reindex(void* parent) override;

            ECS_Acceleration(const f32& aclX = 0.0f, const f32& aclY = 0.0f, const f32& aclZ = 0.0f);
            ECS_Acceleration(const Vec3f& acl);

            Vec3f get_acceleration() const;
            Vec3f& ref_acceleration();
            void add_acceleration(Vec3f force);
            void set_acceleration(Vec3f acceleration);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Acceleration>(*this));
            }
    };
}

#endif