/**
 * @file 
 * ebo.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _EBO_H_
#define _EBO_H_

#include <vector>

#include "types.tpp"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    using namespace omni::types;

    /**
     * @brief EBO - element buffer object, primary 
     * used for storing opengl indices buffer
    */
    class EBO : BO {
        public:
            /**
             * @brief Default construct for EBO
             * 
             * @param indices indices for the EBO buffer
            */
            EBO(const std::vector<u32>& indices);
            
            /**
             * @brief Defulat EBO decostructor
            */
            ~EBO();

            /** @brief Binds EBO opengl buffer object */
            void bind() const override;
            
            /** @brief Unbinds EBO opengl buffer object */
            void unbind() const override;

            /** @brief Terminates EBO opengl buffer object */
            void terminate() const override;
    };
}

#endif