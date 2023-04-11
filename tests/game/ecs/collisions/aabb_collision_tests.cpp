#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().reset();
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp1.is_colliding() == true);
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp1.is_colliding() == true);
        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp2.is_colliding() == true);
        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp2.is_colliding() == true);
        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp1.is_colliding() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp1.is_colliding() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp2.is_colliding() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_AABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_AABBCollider> index1 = e1.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp1 = e1.ref_unsafe<ECS_AABBCollider>(index1);

        ECS_Index<ECS_AABBCollider> index2 = e2.index<ECS_AABBCollider>();
        ECS_AABBCollider& comp2 = e2.ref_unsafe<ECS_AABBCollider>(index2);

        ensure(comp2.is_colliding() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    return 0;
}