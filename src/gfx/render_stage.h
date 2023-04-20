/**
 * @file 
 * render_stage.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _RENDER_STAGE_H_
#define _RENDER_STAGE_H_

#include <functional>

#include "build_in_mesh_data.h"
#include "texture_buffer.h"
#include "raw_mesh_data.h"
#include "frame_buffer.h"
#include "sprite_mesh.h"
#include "renderer.h"
#include "shader.h"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx::texture;

    struct RenderStageProp {
        std::string _stageName = "";
        /** 
         * @brief Pointer to assigned texture buffer,
         * if it is not a null, rendering stage 
         * will render evrethingh into this texture buffer 
        */
        TextureBuffer* _textureBuffer = nullptr;
        
        /**
         * @brief Pointer to shader that was assigned to this RenderStage
         * if it is not null, this shader will be used for rendering
        */
        Shader* _defaultShader = nullptr;

        /** @brief Active mesh date, ofthen there will be quad mesh */
        SpriteMesh _spriteMesh;

        struct RenderStageUniformProp {
            std::function<f32(void)> _screenAspect = [](){ return 1.0f; };
            std::function<Vec3f(void)> _cameraPosition = [](){ return Vec3f{0.0f, 0.0f, 0.0f}; };
            std::function<f32(void)> _cameraZoom = [](){ return 1.0f; };
        } _shaderUniforms;

        struct RenderStageBufferProp {
            Vec4f _clearBufferColor = Vec4f{0.0f, 0.0f, 0.0f, 0.0f}; 
        } _buffer;
    };

    /**
     * @brief RenderStage - class used for stage rendering
     * everything that is rendered inside renderingStageLamda
     * will be rendered inside FrameBuffer, after this frame buffer
     * can be rendered in to the screen buffer or even into another 
     * rendering stage / frame buffer.
    */
    class RenderStage : public FrameBuffer, public RenderStageProp {
        private:
            /**
             * @brief Pointer to active render stage
            */
            static RenderStage* _activeRenderStage;
            
            i32 _stageId;

        public:
            /** @brief Default constructor for RenderStage */
            RenderStage(const RenderStageProp& prop, const i32& stageId);
            
            //void bind() const override;
            //void unbind() const override;
            //void terminate() const override;

            i32 get_stage_id() const;

            /**
             * @brief Binds mesh to the RenderStage instance(usually QUAD mesh)
             * 
             * @param rawMeshData target mesh
            */
            RenderStage& bind_target_mesh(const SpriteMesh& rawMeshData);

            /**
             * @brief Binds texture buffer using pointer to the RenderStage instance
             * 
             * @param textureBuffer target texture buffer pointer
            */
            RenderStage& bind_target_texture_buffer(TextureBuffer *textureBuffer);

            /**
             * @brief Binds texture buffer using reference to the RenderStage instance
             * 
             * @param textureBuffer target texture buffer reference
            */
            RenderStage& bind_target_texture_buffer(TextureBuffer& textureBuffer);

            /**
             * @brief Binds shader using pointer to the RenderStage instance
             * 
             * @param shader target shader pointer
            */
            RenderStage& bind_default_shader(Shader *shader);

            /**
             * @brief Binds shader using reference to the RenderStage instance
             * 
             * @param shader target shader reference
            */
            RenderStage& bind_default_shader(Shader& shader);
            
            /**
             * @brief Renders everything into the 
             * rendering stage frame buffer using rendering lamda
             * 
             * @note Applies shader if it is possible
             * 
             * @param renderingLambda lambda expression 
             * that should be rendered into the 
             * rendering stage frame buffer
            */
            void render_stage_lambda(const std::function<void(void)> renderingLambda);
            
            /**
             * @brief Renders everything into the 
             * rendering stage frame buffer using rendering lamda
             * 
             * @note Do not applies shader
             * 
             * @param renderingLambda lambda expression 
             * that should be rendered into the 
             * rendering stage frame buffer
            */
            void render_stage_lambda_default(const std::function<void(void)> renderingLambda);
            
            /**
             * @brief Renders everything into the 
             * rendering stage frame buffer using rendering lamda,
             * with using provided shader
             * 
             * @note Passes shader that was assigned to the 
             * rendering stage to the rendering stage lambda
             * 
             * @param renderingLambda lambda expression 
             * that should be rendered into the 
             * rendering stage frame buffer
            */
            void render_stage_lambda(const std::function<void(const Shader* shader)> renderingLambda);        

            /**
             * @brief Renders everything into the 
             * screen buffer
             * 
             * @param renderingLambda lambda expression 
             * that should be rendered into the 
             * screen buffer
            */
            static void render_anonymous_stage_lambda(const std::function<void(void)> renderingLambda);

            /** @brief Renders frame buffer as an sprite */
            void present_as_texture() const;

            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param shader target shader
             * @param position uv possition there to render rendering stage texture 
            */
            void present_as_texture(const Shader *shader, const Vec2f &position) const;
            
            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param shader target shader
             * @param rotation the angle to rotate the texture
            */
            void present_as_texture(const Shader *shader, const f32 &rotation) const;
            
            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param shader target shader
             * @param position uv possition there to render rendering stage texture 
             * @param scale the scale of the texture
            */
            void present_as_texture(const Shader *shader, const Vec2f &position, const Vec2f &scale) const;
            
            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param shader target shader
             * @param position uv possition there to render rendering stage texture 
             * @param rotation the angle to rotate the texture
            */
            void present_as_texture(const Shader *shader, const Vec2f &position, const f32 &rotation) const;
            
            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param shader target shader
             * @param position uv possition there to render rendering stage texture 
             * @param rotation the angle to rotate the texture
             * @param scale the scale of the texture
            */
            void present_as_texture(const Shader *shader, const Vec2f &position, const f32 &rotation, const Vec2f &scale) const;

            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param shader target shader
             * @param position uv possition there to render rendering stage texture 
            */
            void present_as_texture(const Vec2f &position) const;

            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param rotation the angle to rotate the texture
            */
            void present_as_texture(const f32 &rotation) const;
                        
            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param position uv possition there to render rendering stage texture 
             * @param scale the scale of the texture
            */
            void present_as_texture(const Vec2f &position, const Vec2f &scale) const;

            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param position uv possition there to render rendering stage texture 
             * @param rotation the angle to rotate the texture
            */
            void present_as_texture(const Vec2f &position, const f32 &rotation) const;

            /**
             * @brief Renders fram buffer as an texture, with applying some transformations
             * 
             * @param position uv possition there to render rendering stage texture 
             * @param rotation the angle to rotate the texture
             * @param scale the scale of the texture
            */
            void present_as_texture(const Vec2f &position, const f32 &rotation, const Vec2f &scale) const;
    
            static RenderStage* get_active_render_stage();
    };
}

#endif