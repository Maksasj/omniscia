/**
 * @file 
 * vbo.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _VBO_H_
#define _VBO_H_

#include <vector>

#include "omni_types.tpp"
#include "vertex.h"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    using namespace omni::types;

    /**
     * @brief VBO - vertex buffer object class 
     * used for storing and managing
     * opengl vertex buffer object
    */
    class VBO : private BO {
        private:

        public:
            /**
             * @brief Default VBO constructor, 
             * creates opengl vbo, and assignes 
             * Vertex data to it 
             * 
             * @param vertices array of Vertices
            */
            VBO(const std::vector<Vertex>& vertices);

            /** @brief Binds VBO as an active opengl vertex buffer object */
            void bind() const override;
            
            /** @brief Unbinds opengl vertex buffer object */
            void unbind() const override;

            /** @brief Terminates opengl vertex buffer obeject */
            void terminate() const override;
    };
}

#endif