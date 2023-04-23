/**
 * @file 
 * renderer.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMMNISCIA_RENDERER_H_
#define _OMMNISCIA_RENDERER_H_

#include <iostream>

#include "sprite.h"

#include "types.tpp"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omniscia::core;

    /**
     * @brief Renderer - singleton class used 
     * only for some openlgl initialization
    */
    class Renderer {
        private:

        public:
            /** @brief Initializes glfw */
            static void init();
            
            /** @brief Initializes glad */
            static void load_gl();

            /**
             * @brief clears active frame buffer
             * 
             * @param color that should be used 
             * for clearing frame buffer 
             * (it fills active fram buffer with this color) 
            */
            static void clear_buffer(const Vec4f& color);
    };
}

#endif
