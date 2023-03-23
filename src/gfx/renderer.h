#ifndef _OMMNISCIA_RENDERER_H_
#define _OMMNISCIA_RENDERER_H_

#include <iostream>

#include "types.tpp"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omniscia::core;

    class Renderer {
        public:
            static void init();
            static void loadGL();
            static void clearBuffer(const Vec4f& color);
    };
}

#endif
