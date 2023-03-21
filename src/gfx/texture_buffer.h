#ifndef _TEXTURE_BUFFER_H_
#define _TEXTURE_BUFFER_H_

#include <iostream>

#include <glad/glad.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "bo.h"
#include "types.tpp"

namespace omniscia::gfx::texture {
    using namespace omniscia::core;

    class TextureBuffer : public BO {
        public:
            TextureBuffer();
            TextureBuffer(const u32& width, const u32& height);

            void bind() const override;
            void unbind() const override;
    };
}

#endif