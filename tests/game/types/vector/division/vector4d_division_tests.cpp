#include "test.h"

int main() {
    USING_OMNISCIA_NAMESPACES

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        
        auto c = a / 1.0f;

        ensure(c.to_string() == "1 1 1 1");
    }

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        
        auto c = a / 2.0f;

        ensure(c.to_string() == "0.5 0.5 0.5 0.5");
    }

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        
        auto c = a / 3.0f;

        ensure(c.to_string() == "0.333333 0.333333 0.333333 0.333333");
    }

    TEST_CASE {
        Vec4f a = Vec4f{1.0f, 1.0f, 1.0f, 1.0f};
        
        auto c = a / 0.5f;

        ensure(c.to_string() == "2 2 2 2");
    }

    TEST_CASE {
        Vec4f a = Vec4f{2.0f, 2.0f, 2.0f, 2.0f};
        
        auto c = a / 0.5f;

        ensure(c.to_string() == "4 4 4 4");
    }

    TEST_CASE {
        Vec4f a = Vec4f{641856.2981f, 471899.91922f, 471899.91922f, 641856.2981f};
        
        auto c = a / 9158.11266f;

        ensure(c.to_string() == "70.0861 51.5281 51.5281 70.0861");
    }

    return 0;
}