/**
 * @file 
 * frame_buffer.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include "texture_buffer.h"
#include "omni_types.tpp"
#include "gfx/gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    using namespace omni::types;

    /**
     * @brief FrameBuffer - frame buffer opengl object,
     * used storing frame data, used by stage rendering
     * as well as by texture rendering
    */
    class FrameBuffer : BO {
        private:

        public:
            /** @brief Default constructor for FrameBuffer */
            FrameBuffer();
            
            /** @brief Default deconstructor for FrameBuffer */
            ~FrameBuffer();
            
            /** @brief Binds opengl frame buffer */
            void bind() const override;
            
            /** @brief Unbinds opengl frame buffer */
            void unbind() const override;

            /**
             * @brief Binds TextureBuffer to this FrameBuffer
             * primary used for stage rendering, and rendering 
             * to separate frame buffer
             * 
             * @param textureBuffer reference to the target texture buffer 
            */
            void bind_target_texture_buffer(const omniscia::gfx::texture::TextureBuffer& textureBuffer);
    };
}

#endif