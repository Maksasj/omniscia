#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 9.1f};
        Vec4f b = Vec4f{-1.0f, -1.0f, 1.0f, 0.9f};
        
        auto c = a + b;

        ensure(c.to_string() == "0 0 2 10");
    }

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 5.0f, 1.0f};
        Vec4f b = Vec4f{-2.0f, -2.0f, 5.0f, 0.0f};
        
        auto c = a + b;

        ensure(c.to_string() == "-1 -1 10 1");
    }

    TEST_CASE {
        Vec4f a = Vec4f{141.1498f, 1915.155f, 0.0f, 129.1f};
        Vec4f b = Vec4f{-25929.11129f, -2985.49182f, 1.0f, 0.1f};
        
        auto c = a + b;

        ensure(c.to_string() == "-25788 -1070.34 1 129.2");
    }

    return 0;
}