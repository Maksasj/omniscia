/**
 * @file 
 * vao.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _VAO_H_
#define _VAO_H_

#include <vector>

#include "omni_types.tpp"
#include "vertex.h"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    using namespace omni::types;

    /**
     * @brief VAO - class used for managing 
     * opengl vertex array objects
    */
    class VAO : BO {
        private:

        public:
            /** @brief Default VAO constructor */
            VAO();
            
            /** @brief Default VAO deconstructor */
            ~VAO();

            /**
             * @brief Links atributes to the vao(usually vertices, and indices)
             * 
             * @param index of the attribute
             * @param componentsNumber number of the elements
             * @param type type of the elements (GL_FLOAT, etc)
             * @param strideSize size of the memory stride
             * @param offset memory offset
            */
            void link_attribute(u32 index, u32 componentsNumber, u32 type, u32 strideSize, void* offset);

            /** @brief Binds vao as an active opengl vao */
            void bind() const override;
            
            /** @brief Unbinds vao as an active opengl vao */
            void unbind() const override;

            /** @brief Terminates opengl vao */
            void terminate() const override;
    };
}

#endif