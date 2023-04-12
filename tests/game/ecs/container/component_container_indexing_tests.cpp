#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);

        auto index = container.index<ECS_Positioned>();

        ensure((index.is_success()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Scaled>(new Entity(), 0.0f, 0.0f);

        auto index = container.index<ECS_Scaled>();

        ensure((index.is_success()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        auto index = container.index<ECS_2DPhysicsRigidbody>();

        ensure((index.is_success()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);

        auto index = container.index<ECS_2DPhysicsRigidbody>();

        ensure(!(index.is_success()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        auto index = container.index<ECS_Scaled>();

        ensure(!(index.is_success()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        auto index = container.index<ECS_SpriteRenderer>();

        ensure(!(index.is_success()));
    }

    return 0;
}