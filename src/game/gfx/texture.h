/**
 * @file 
 * texture.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "texture_buffer.h"
#include "gfx/gfx.h"

namespace omniscia::gfx::texture {
    using namespace omni::types;

    /**
     * @brief Texture - class used for storing 
     * texture buffer, and some other texture
     * parameters, widht height and etc
    */
    class Texture : public TextureBuffer {
        protected:
            /** @brief Width of the texture */
            u32 _width;
            
            /** @brief Height of the texture */
            u32 _height;

            /**
             * @brief Aspect ratio of the texture, (used for rendering)
            */
            f32 _aspect;

            /**
             * @brief Number of the color channels of the texture (rgb - 3, rgba - 4)
            */
            u32 _colorChannels;
        
        public:
            /** @brief Default Texture constructor */
            Texture();

            /**
             * @brief Function used for getting width of the texture
             * 
             * @return u32 - widht of the texture 
            */
            u32 get_width() const;
            
            /**
             * @brief Function used for getting height of the texture
             * 
             * @return u32 - height of the texture 
            */
            u32 get_height() const;
            
            /**
             * @brief Function used for getting aspect ratio of the texture
             * 
             * @return f32 - aspect ratio of the texture
            */
            f32 get_aspect() const;

            /**
             * @brief Function used for getting number of color channels of the texture
             * 
             * @return u32 - number of the color channels of the texture
            */
            u32 get_color_channels() const;

            /**
             * @brief Sets width of the texture
             * 
             * @param width - new width of the texture
            */
            void set_width(u32 width);
            
            /**
             * @brief Sets height of the texture
             * 
             * @param width - new height of the texture
            */
            void set_height(u32 height);

            /**
             * @brief Sets apspect ratio of the texture
             * 
             * @param width - new apspect ratio of the texture
            */
            void set_aspect(f32 aspect);

            /**
             * @brief Sets the number of color channels of the texture
             * 
             * @param colorChannels - new number of the color channels
            */
            void set_color_channels(u32 colorChannels);
    };
}

#endif