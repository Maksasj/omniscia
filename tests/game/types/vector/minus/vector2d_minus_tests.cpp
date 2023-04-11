#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES

    TEST_CASE {
        Vec2f a = Vec2f{1.0f, 1.0f};
        Vec2f b = Vec2f{1.0f, 1.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "0 0");
    }

    TEST_CASE {
        Vec2f a = Vec2f{1.0f, 1.0f};
        Vec2f b = Vec2f{2.0f, 2.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "-1 -1");
    }

    TEST_CASE {
        Vec2f a = Vec2f{141.1498f, 1915.155f};
        Vec2f b = Vec2f{25929.11129f, 2985.49182f};
        
        auto c = a - b;

        ensure(c.to_string() == "-25788 -1070.34");
    }

    return 0;
}