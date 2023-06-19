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

#ifndef _INSTANCING_SPRITE_H_
#define _INSTANCING_SPRITE_H_

#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "texture_manager.h"
#include "texture.h"
#include "properties.h"
#include "omni_types.tpp"
#include "shader.h"
#include "timesystem.h"
#include "gfx.h"
#include "ubo.h"

namespace omniscia::gfx::sprite {
    using namespace omni::types;
    using namespace omniscia::core;
    using namespace omniscia::gfx::texture;
    
    class InstancingSprite {
        private:
            SpriteMesh _spriteMesh;

            Texture *_texture;
            UBO _ubo;
            
        public:
            InstancingSprite(const std::string& textureId);
            InstancingSprite(const RawMeshData& spriteMesh, const std::string& textureId);

            void bind() const;
            void unbind() const;

            void render(const Shader *shader, const std::vector<InstancingData>& instancingData, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset, const bool& horizontalFlip, const bool& verticalFlip) const;
            
            void set_texture_by_id(const std::string& textureId);
            
            SpriteMesh& get_mesh();
            u64 byte_size() const;
    };
}

#endif