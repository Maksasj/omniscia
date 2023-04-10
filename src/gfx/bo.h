/**
 * @file 
 * bo.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _BO_H_
#define _BO_H_

#include "types.tpp"

namespace omniscia::gfx {
    /**
     * @brief BO - buffer object, main opengl 
     * object, used for VBO, EBO, Texture buffer and etc. 
    */
    class BO {
        protected:
            /** @brief ID of the opengl buffer object */
            u32 _ID;

        public:
            /** @brief Virtual method used for binding buffer object */
            virtual void bind() const {};
            
            /** @brief Virtual method used for unbinding buffer object */
            virtual void unbind() const {};

            /** @brief Virtual method used for deleting buffer object */
            virtual void terminate() const {};

            /**
             * @brief Returns buffer object id
             * 
             * @return buffer object id
            */
            u32 get_id() const;

            /**
             * @brief Returns reference to the buffer object id
             * 
             * @return reference to the buffer object id
            */
            u32* get_id_ref();
    };
}

#endif