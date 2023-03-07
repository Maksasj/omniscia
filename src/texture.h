#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>

#include "texture_buffer.h"

namespace omniscia::renderer::texture {
    class Texture : public TextureBuffer {
        public:
            Texture();

            //void bind() override;
            //void unbind() override;
    };
}

#endif