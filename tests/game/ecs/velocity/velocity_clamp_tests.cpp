#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{0.0f, 0.0f, 0.0f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();

        ensure((comp.get_velocity() == Vec3f{0.0f, 0.0f, 0.0f}));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{1.0f, 1.0f, 1.0f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();

        ensure((comp.get_velocity() == Vec3f{1.0f, 1.0f, 1.0f}));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{24992.14929f, 19129.1992f, 984191.14981f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();

        ensure((comp.get_velocity() == Vec3f{1.0f, 1.0f, 984191.14981f}));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{1991.14999f, 12982.19298f, 149222.51911f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();

        ensure((comp.get_velocity() == Vec3f{1.0f, 1.0f, 149222.51911f}));
    }
    
    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{0.0f, 0.0f, 0.0f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();

        ensure((comp.get_velocity().to_string() == "0 0 0"));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{2.0f, 3.0f, -5.0f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();

        ensure((comp.get_velocity().to_string() == "1 1 -5"));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Velocity>(Vec3f{-8.0f, 19.0f, 910.0f}, Vec2f{1.0f, -1.0f}, Vec2f{1.0f, -1.0f});
        
        e1.time_sync();

        ECS_Index<ECS_Velocity> index = e1.index<ECS_Velocity>();
        ECS_Velocity& comp = e1.ref_unsafe<ECS_Velocity>(index);
        comp.clamp_velocity();
        std::cout << comp.get_velocity().to_string() << "\n";
        ensure((comp.get_velocity().to_string() == "-1 1 910"));
    }

    return 0;
}