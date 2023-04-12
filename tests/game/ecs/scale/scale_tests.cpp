#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES
    
    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Scaled>(0.1f, 0.1f);
        
        e1.time_sync();

        ECS_Index<ECS_Scaled> index = e1.index<ECS_Scaled>();
        ECS_Scaled& comp = e1.ref_unsafe<ECS_Scaled>(index);

        ensure((comp.get_scale() == Vec2f{0.1f, 0.1f}));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Scaled>(0.81978f, 0.91492f);
        
        e1.time_sync();

        ECS_Index<ECS_Scaled> index = e1.index<ECS_Scaled>();
        ECS_Scaled& comp = e1.ref_unsafe<ECS_Scaled>(index);

        ensure((comp.get_scale() == Vec2f{0.81978f, 0.91492f}));
    }
    
    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Scaled>(0.81978f, 0.91492f);
        
        e1.time_sync();

        ECS_Index<ECS_Scaled> index = e1.index<ECS_Scaled>();
        ECS_Scaled& comp = e1.ref_unsafe<ECS_Scaled>(index);

        ensure((comp.get_scale().to_string() == "0.81978 0.91492"));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Scaled>(0.1f, 0.999f);
        
        e1.time_sync();

        ECS_Index<ECS_Scaled> index = e1.index<ECS_Scaled>();
        ECS_Scaled& comp = e1.ref_unsafe<ECS_Scaled>(index);

        ensure((comp.get_scale().to_string() == "0.1 0.999"));
    }

    TEST_CASE {
        Entity e1;
            e1.add<ECS_Positioned>(0.0f, 0.0f);
            e1.add<ECS_Scaled>(149891.0f, -191919.0f);
        
        e1.time_sync();

        ECS_Index<ECS_Scaled> index = e1.index<ECS_Scaled>();
        ECS_Scaled& comp = e1.ref_unsafe<ECS_Scaled>(index);

        ensure((comp.get_scale().to_string() == "149891 -191919"));
    }

    return 0;
}