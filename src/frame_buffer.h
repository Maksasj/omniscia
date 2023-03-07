#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include <glad/glad.h>

#include "texture_buffer.h"

#include "bo.h"
#include "types.h"

namespace omniscia::renderer {
    class FrameBuffer : BO {
        public:
            FrameBuffer();
            
            void bind() override;
            void unbind() override;

            void terminate() override;

            void bind_target_texture_buffer(const omniscia::renderer::texture::TextureBuffer& textureBuffer);
    };
}

#endif