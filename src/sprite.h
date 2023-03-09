#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <glad/glad.h>

#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "texture_manager.h"
#include "texture.h"

#include "shader.h"

#include "types.h"

namespace omniscia::renderer::sprite {
    using namespace omniscia::renderer::texture;
    using namespace omniscia::core;
    
    class Sprite {
        private:
            SpriteMesh spriteMesh;
            Texture *texture;
        public:
            Sprite(const std::string& texture_id);
            Sprite(const std::string& texture_id, const Vec3f& scale);

            void bind() const;
            void unbind() const;
            
            void render();

            void render(const Shader *shader, const Vec2f &position) const;
            void render(const Shader *shader, const float &rotation) const;
            void render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const;
            void render(const Shader *shader, const Vec2f &position, const float &rotation) const;
            void render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const;
            
            void set_texture_by_id(const std::string& texture_id);
            SpriteMesh& get_mesh();
    };
}

#endif