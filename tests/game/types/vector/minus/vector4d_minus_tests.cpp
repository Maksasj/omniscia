#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        Vec4f b = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "0 0 0 0");
    }

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        Vec4f b = Vec4f{2.0f, 2.0f, 2.0f, 2.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "-1 -1 -1 -1");
    }

    TEST_CASE {
        Vec4f a = Vec4f{141.1498f, 1915.155f, 1.0f, 2.0f};
        Vec4f b = Vec4f{25929.11129f, 2985.49182f, 1.0f, 1.0f};
        
        auto c = a - b;

        ensure(c.to_string() == "-25788 -1070.34 0 1");
    }

    return 0;
}