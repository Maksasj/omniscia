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
    
    class Sprite {
        private:
            SpriteMesh spriteMesh;
            Texture *texture;
        public:
            Sprite(const std::string& texture_id);
            Sprite(const std::string& texture_id, const Vec3f& scale);
            Sprite(const RawMeshData& spriteMesh, const std::string& texture_id);
            Sprite(const RawMeshData& spriteMesh, const std::string& texture_id, const Vec3f& scale);

            void bind() const;
            void unbind() const;

            void render(const Shader *shader) const;
            void render(const Shader *shader, const Vec2f &position) const;
            void render(const Shader *shader, const float &rotationAngle) const;
            void render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const;
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle) const;
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale) const;
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset) const;
            
            void render(const Shader *shader, const Matrix<f32, 2, 2> &rotation) const;
            void render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation) const;
            void render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation, const Vec2f &scale) const;
            void render(const Shader *shader, const Vec2f &position, const Matrix<f32, 2, 2> &rotation, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset) const;
            
            void render(const Shader *shader, const Vec2f &position, const float &rotationAngle, const Vec2f &scale, const Vec2f &spriteFrameSize, const Vec2f &spriteSheetOffset,const bool& horizontalFlip,const bool& verticalFlip) const;

            void set_texture_by_id(const std::string& texture_id);

            SpriteMesh& get_mesh();
            
            u64 byte_size() const { 
                return sizeof(Texture*) + spriteMesh.byte_size();
            }
    };
}

#endif