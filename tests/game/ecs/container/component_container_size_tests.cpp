#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);
        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);
        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);

        ensure((container.size() == 3));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Scaled>(new Entity(), 0.0f, 0.0f);
        container.add<ECS_Scaled>(new Entity(), 0.0f, 0.0f);

        ensure((container.size() == 2));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        ensure((container.size() == 0));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_Positioned>(new Entity(), 0.0f, 0.0f);

        ensure(!(container.size() == 2));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        ensure(!(container.size() == 0));
    }

    TEST_CASE {
        ECS_ComponentContainer container;

        container.add<ECS_2DPhysicsRigidbody>(new Entity());

        ensure(!(container.size() == 999));
    }

    return 0;
}