#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"

#include "shader_manager.h"
#include "shader_asset.h"

namespace omniscia::renderer {
    using namespace omniscia::core;

    class Shader {

        u32 _vertexShaderTmp;
        u32 _fragmentShaderTmp;

        ShaderAsset* _shaderAssetVertex;
        ShaderAsset* _shaderAssetFragment;

        static std::string load_from_file(std::string path);

        public:
        u32 _shaderProgram;
            Shader(const std::string& shaderVertId, const std::string& shaderFragId);

            i32 try_compile();

            void compile();

            void activate();

            void set_uniform_f32(const char *uniform, f32 value);
            void set_uniform_i32(const char *uniform, i32 value);
            
            void terminate();
    };
}

#endif