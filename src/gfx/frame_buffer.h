#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include "texture_buffer.h"
#include "types.tpp"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    class FrameBuffer : BO {
        public:
            FrameBuffer();
            ~FrameBuffer();
            
            void bind() const override;
            void unbind() const override;

            void bind_target_texture_buffer(const omniscia::gfx::texture::TextureBuffer& textureBuffer);
    };
}

#endif