#ifndef _OMMNISCIA_RENDERER_H_
#define _OMMNISCIA_RENDERER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "types.tpp"

namespace omniscia::renderer {
    using namespace omniscia::core;

    class Renderer {
        public:
            static void init();
            static void loadGL();
            static void clearBuffer(const Vec4f& color);
    };
}

#endif
