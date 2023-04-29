/**
 * @file 
 * sprite.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "texture_manager.h"
#include "texture.h"
#include "properties.h"
#include "types.tpp"
#include "shader.h"
#include "gfx.h"

namespace omniscia::gfx::sprite {
    using namespace omniscia::gfx::texture;
    using namespace omniscia::core;
    
    /**
     * @brief Sprite - class used 
     * for storing single sprite instance
     * used for only rendering 
    */
    class Sprite {
        private:
            /** @brief SpriteMesh instance of the current sprite */
            SpriteMesh _spriteMesh;
            
            /** @brief Pointer to the _texture that is associated with this sprite */
            Texture *_texture;
            
        public:
            /**
             * @brief Constructs a sprite instance, 
             * using provided _texture id, for 
             * sprite mesh it will use default quad mesh
             * 
             * @param textureId id of the _texture 
            */
            Sprite(const std::string& textureId);
            
            /**
             * @brief Constructs a sprite instance, 
             * using provided _texture id, for 
             * sprite mesh it will use default quad mesh, 
             * and also applying scale transformation 
             * to the sprite mesh
             * 
             * @param textureId id of the _texture 
             * @param scale new scale of the sprite mesh 
            */
            Sprite(const std::string& textureId, const Vec3f& scale);

            /**
             * @brief Constructs new sprite instance, 
             * using provided raw sprite mesh 
             * data as well as _texture id 
             * 
             * @param _spriteMesh raw sprite mesh data, that will be used for initializing sprite mesh
             * @param textureId id of the texutre
            */
            Sprite(const RawMeshData& _spriteMesh, const std::string& textureId);
            
            /**
             * @brief Constructs new sprite instance, 
             * using provided raw sprite mesh 
             * data as well as _texture id, and applying scale tranformation 
             * 
             * @param _spriteMesh raw sprite mesh data, that will be used for initializing sprite mesh
             * @param textureId id of the texutre
             * @param scale new scale of the sprite mesh
            */
            Sprite(const RawMeshData& _spriteMesh, const std::string& textureId, const Vec3f& scale);

            /** @brief Binds sprite mesh and _texture for opengl rendering */
            void bind() const;
            
            /** @brief Unbinds sprite mesh and _texture for opengl rendering */
            void unbind() const;

            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
            */
            void render(const Shader *shader) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
            */
            void render(const Shader *shader, const Vec2f &position) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param rotationAngle the angle by which the sprite should be rotated
            */
            void render(const Shader *shader, const float &rotationAngle) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param scale the uv scale by which the sprite should be scaled
            */
            void render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param scale the uv scale by which the sprite should be scaled
             * @param horizontalFlip bolean, does sprite should be flipped horizontally
             * @param verticalFlip bolean, does sprite should be flipped vertically
            */
            void render(const Shader *shader, const Vec2f &position, const Vec2f &scale, const bool& horizontalFlip, const bool& verticalFlip) const;

            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotationAngle the angle by which the sprite should be rotated
            */
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotationAngle the angle by which the sprite should be rotated
             * @param scale the uv scale by which the sprite should be scaled
            */
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotationAngle the angle by which the sprite should be rotated
             * @param scale the uv scale by which the sprite should be scaled
             * @param spriteFrameSize uv size of the frame that will be rendered (used for sprite sheets)
             * @param spriteSheetOffset uv offset of the frame that will be rendered (used for sprite sheets)
            */
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param rotation the rotation matrix by which the sprite should be rotated
            */
            void render(const Shader *shader, const Matrix<f32, 2, 2> &rotation) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotation the rotation matrix by which the sprite should be rotated
            */
            void render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotation the rotation matrix by which the sprite should be rotated
             * @param scale the uv scale by which the sprite should be scaled
            */
            void render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation, const Vec2f &scale) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotation the rotation matrix by which the sprite should be rotated
             * @param scale the uv scale by which the sprite should be scaled
             * @param spriteFrameSize uv size of the frame that will be rendered (used for sprite sheets)
             * @param spriteSheetOffset uv offset of the frame that will be rendered (used for sprite sheets)
            */
            void render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset) const;
            
            /**
             * @brief Renders sprite instance into the binded frame buffer, using specified parameters
             * 
             * @param shader that should be used for rendering  
             * @param position uv position where to render sprite
             * @param rotation the rotation matrix by which the sprite should be rotated
             * @param scale the uv scale by which the sprite should be scaled
             * @param spriteFrameSize uv size of the frame that will be rendered (used for sprite sheets)
             * @param spriteSheetOffset uv offset of the frame that will be rendered (used for sprite sheets)
             * @param horizontalFlip bolean, does sprite should be flipped horizontally
             * @param verticalFlip bolean, does sprite should be flipped vertically
            */
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset, const bool& horizontalFlip, const bool& verticalFlip) const;

            /**
             * @brief Sets the _texture by it id
             * 
             * @param textureId _texture id that need to be set
            */
            void set_texture_by_id(const std::string& textureId);

            /**
             * @brief References sprite mesh of current the sprite instance
             * 
             * @return SpriteMesh reference
            */
            SpriteMesh& get_mesh();
            
            /**
             * @brief Calculates bytes size of this sprite mesh instance
             * 
             * @return byte size
            */
            u64 byte_size() const;
    };
}

#endif