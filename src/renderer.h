#ifndef _OMMNISCIA_RENDERER_H_
#define _OMMNISCIA_RENDERER_H_

#include <glad/glad.h>

namespace omniscia::renderer {
    class Renderer {
        public:
            static void init() {
                glfwInit();
                
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            }

            static void loadGL() {
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    std::cout << "Failed to initialize GLAD" << std::endl;
                }
            }
    };
}

#endif
