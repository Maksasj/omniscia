#ifndef _OMMNISCIA_RENDERER_H_
#define _OMMNISCIA_RENDERER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace omniscia::renderer {
    class Renderer {
        public:
            static void init();
            static void loadGL();
    };
}

#endif
