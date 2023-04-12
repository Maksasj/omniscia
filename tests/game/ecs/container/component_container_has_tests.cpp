#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);

        ensure((container.has<ECS_Positioned>()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Scaled>(new Entity(), 0.0f, 0.0f);

        ensure((container.has<ECS_Scaled>()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        ensure((container.has<ECS_2DPhysicsRigidbody>()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);

        ensure(!(container.has<ECS_2DPhysicsRigidbody>()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        ensure(!(container.has<ECS_Positioned>()));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        ensure(!(container.has<ECS_Scaled>()));
    }

    return 0;
}