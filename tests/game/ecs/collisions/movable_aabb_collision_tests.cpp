#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().reset();
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp1.is_colliding_by_x() == true);
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp1.is_colliding_by_y() == true);
        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp2.is_colliding_by_x() == true);
        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 1.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 1.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();

        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp2.is_colliding_by_y() == true);
        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp1.is_colliding_by_x() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp1.is_colliding_by_y() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp2.is_colliding_by_x() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(50.0f, 50.0f);
            e1.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
        
        Entity e2;
            e2.add<ECS_Positioned>(0.0f, 0.0f);
            e2.add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_AmbientEntities);
            e2.time_sync();

        ECS_AABBColliderSystem::get_instance().time_sync();
        e1.time_sync();
        e2.time_sync();
        
        ECS_AABBColliderSystem::get_instance().update();

        ECS_Index<ECS_MovableAABBCollider> index1 = e1.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp1 = e1.ref_unsafe<ECS_MovableAABBCollider>(index1);

        ECS_Index<ECS_MovableAABBCollider> index2 = e2.index<ECS_MovableAABBCollider>();
        ECS_MovableAABBCollider& comp2 = e2.ref_unsafe<ECS_MovableAABBCollider>(index2);

        ensure(comp2.is_colliding_by_y() == false);

        ECS_AABBColliderSystem::get_instance().reset();
    }

    return 0;
}