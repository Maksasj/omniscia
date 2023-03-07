#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <glad/glad.h>

#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "texture.h"

#include "types.h"

namespace omniscia::renderer::sprite {
    using namespace omniscia::renderer::texture;
    
    class Sprite {
        private:
            SpriteMesh spriteMesh;
            Texture texture;
        public:
            Sprite() : spriteMesh(BuildInMeshData::QUAD_MESH_DATA) , texture() {
                
            }

            void bind() {
                texture.bind();
                spriteMesh.bind();
            }
    };
}

#endif