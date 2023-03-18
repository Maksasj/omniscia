#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <glad/glad.h>

#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "texture_manager.h"
#include "texture.h"

#include "properties.h"
#include "shader.h"

#include "types.tpp"

namespace omniscia::renderer::sprite {
    using namespace omniscia::renderer::texture;
    using namespace omniscia::core;
    
    class Sprite {
        private:
            SpriteMesh spriteMesh;
            Texture *texture;
        public:
            Sprite();
            Sprite(const std::string& texture_id);
            Sprite(const std::string& texture_id, const Vec3f& scale);

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
            
            void set_texture_by_id(const std::string& texture_id);

            SpriteMesh& get_mesh();
    };
}

#endif