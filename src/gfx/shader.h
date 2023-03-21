#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "types.tpp"

#include "shader_manager.h"
#include "shader_asset.h"

namespace omniscia::gfx {
    using namespace omniscia::core;

    class Shader {
        u32 _shaderProgram;

        u32 _vertexShaderTmp;
        u32 _fragmentShaderTmp;

        ShaderAsset* _shaderAssetVertex;
        ShaderAsset* _shaderAssetFragment;

        static std::string load_from_file(std::string path);

        public:
            Shader(const std::string& shaderVertId, const std::string& shaderFragId);

            i32 try_compile();

            void compile();

            void activate();

            void set_uniform_f32(const char *uniform, f32 value) const;
            void set_uniform_i32(const char *uniform, i32 value) const;
            void set_uniform_vec2f(const char *uniform, Vec2f value) const;
            void set_uniform_vec2i(const char *uniform, Vec2i value) const;
            void set_uniform_vec3f(const char *uniform, Vec3f value) const;
            void set_uniform_vec3i(const char *uniform, Vec3i value) const;

            void set_uniform_mat2x2f(const char *uniform, Matrix<f32, 2, 2> value) const;

            void terminate();
    };
}

#endif