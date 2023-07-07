/**
 * @file 
 * texture_buffer.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _TEXTURE_BUFFER_H_
#define _TEXTURE_BUFFER_H_

#include <iostream>

#include "stb_image.h"
#include "omni_types.tpp"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx::texture {
    using namespace omni::types;

    /**
     * @brief TextureBuffer - class used for
     * managing opengl texture buffer
     * (instance of the buffer object)
    */
    class TextureBuffer : public BO {
        private:

        public:
            /** @brief Defualt TextureBuffer constructor */
            TextureBuffer();
            
            /**
             * @brief Constructs texture buffer, using some provided metrics
             * 
             * @param width in pixels of the texture buffer
             * @param height in pixels of the texture buffer
            */
            TextureBuffer(const u32& width, const u32& height);

            /** @brief Binds Texture buffer as an active opengl texture buffer */
            void bind() const override;
            
            /** @brief Unbinds Texture buffer as an active opengl texture buffer */
            void unbind() const override;
    };
}

#endif