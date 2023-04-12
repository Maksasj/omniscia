#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES

    TEST_CASE {
        Vec3f a = Vec3f{1.0f, 1.0f, 1.0f};
        Vec3f b = Vec3f{1.0f, 1.0f, 1.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "0 0 0");
    }

    TEST_CASE {
        Vec3f a = Vec3f{1.0f, 1.0f, 1.0f};
        Vec3f b = Vec3f{2.0f, 2.0f, 2.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "-1 -1 -1");
    }

    TEST_CASE {
        Vec3f a = Vec3f{141.1498f, 1915.155f, 1.0f};
        Vec3f b = Vec3f{25929.11129f, 2985.49182f, 1.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "-25788 -1070.34 0");
    }

    return 0;
}