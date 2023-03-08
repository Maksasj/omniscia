#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <glad/glad.h>

#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "texture_manager.h"
#include "texture.h"

#include "types.h"

namespace omniscia::renderer::sprite {
    using namespace omniscia::renderer::texture;
    using namespace omniscia::core;
    
    class Sprite {
        private:
            SpriteMesh spriteMesh;
            Texture *texture;
        public:
            Sprite(const std::string& texture_id) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) {
                texture = TextureManager::get(texture_id).get_asset();
            }

            Sprite(const std::string& texture_id, const Vec3f& scale) : spriteMesh(BuildInMeshData::QUAD_MESH_DATA, scale) {
                texture = TextureManager::get(texture_id).get_asset();
            }

            void set_texture_by_id(const std::string& texture_id) {
                texture = TextureManager::get(texture_id).get_asset();
            }

            void bind() {
                texture->bind();
                spriteMesh.bind();
            }

            void unbind() {
                texture->unbind();
                //spriteMesh.unbind();
            }
            
            SpriteMesh& get_mesh() {
                return spriteMesh;
            }

            void draw() {
                bind(); 
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                unbind();
            }
    };
}

#endif