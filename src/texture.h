#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>

#include "texture_buffer.h"

namespace omniscia::renderer::texture {
    class Texture : public TextureBuffer {
        protected:
            u32 _width;
            u32 _height;

            f32 _aspect;

            u32 _colorChannels;
        public:
            Texture();

            u32 get_width() const {
                return _width;
            }

            u32 get_height() const {
                return _height;
            }

            f32 get_aspect() const {
                return _aspect;
            }

            u32 get_color_channels() const {
                return _colorChannels;
            }

            void set_width(u32 width) {
                _width = width;
            }
            void set_height(u32 height) {
                _height = height;
            }
            void set_aspect(f32 aspect) {
                _aspect = aspect;
            }
            void set_color_channels(u32 colorChannels) {
                _colorChannels = colorChannels;
            }
    };
}

#endif