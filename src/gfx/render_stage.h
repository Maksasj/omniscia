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

namespace omniscia::gfx {
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx::texture;

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
            void render_stage_lambda(const std::function<void(const Shader* shader)> rendering_lambda) const;        

            static void render_anonymous_stage_lambda(const std::function<void(void)> rendering_lambda);

            void present_as_texture() const;

            void present_as_texture(const Shader *shader, const Vec2f &position) const;
            void present_as_texture(const Shader *shader, const float &rotation) const;
            void present_as_texture(const Shader *shader, const Vec2f &position, const Vec2f &scale) const;
            void present_as_texture(const Shader *shader, const Vec2f &position, const float &rotation) const;
            void present_as_texture(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const;

            void present_as_texture(const Vec2f &position) const;
            void present_as_texture(const float &rotation) const;
            void present_as_texture(const Vec2f &position, const Vec2f &scale) const;
            void present_as_texture(const Vec2f &position, const float &rotation) const;
            void present_as_texture(const Vec2f &position, const float &rotation, const Vec2f &scale) const;
    };
}

#endif