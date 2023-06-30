#ifndef _OMNISCIA_EDITOR_WINDOW_H_
#define _OMNISCIA_EDITOR_WINDOW_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

namespace omniscia_editor {
    class Window {
        private:
            GLFWwindow* window;

            static Window* activeInstance;
        public:

            Window() {
                window = glfwCreateWindow(640, 480, "Omniscia Level Editor", NULL, NULL);
                
                glfwMakeContextCurrent(window);

                activeInstance = this;
            }

            GLFWwindow* get_backend() {
                return window;
            }

            static Window* get_instance() {
                return activeInstance;
            }
    };
}

#endif
