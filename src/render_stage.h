#ifndef _RENDER_STAGE_H_
#define _RENDER_STAGE_H_

#include <glad/glad.h>
#include <functional>

#include "frame_buffer.h"
#include "texture_buffer.h"
#include "raw_mesh_data.h"
#include "sprite_mesh.h"
#include "build_in_mesh_data.h"
#include "shader.h"

namespace omniscia::renderer {
    using namespace omniscia::renderer::sprite;
    using namespace omniscia::renderer::texture;

    class RenderStage : public FrameBuffer {
        private:
            SpriteMesh _spriteMesh;
            TextureBuffer *_textureBuffer;
            Shader *_shader;
        public:
            RenderStage();
            
            //void bind() const override;
            //void unbind() const override;
            //void terminate() const override;

            void bind_target_mesh(const RawMeshData& rawMeshData);
            void bind_target_mesh(const RawMeshData& rawMeshData, const Vec3f scale);

            void bind_target_texture_buffer(TextureBuffer *textureBuffer);
            void bind_target_texture_buffer(TextureBuffer& textureBuffer);

            void bind_default_shader(Shader *shader);
            void bind_default_shader(Shader& shader);
            
            void render_stage_lambda(const std::function<void(void)> rendering_lambda) const;
            void render_stage_lambda_default(const std::function<void(void)> rendering_lambda) const;
            static void render_anonymous_stage_lambda(const std::function<void(void)> rendering_lambda);

            void present_as_texture() const;
    };
}

#endif