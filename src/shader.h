#ifndef _SHADER_OBJECT_H_
#define _SHADER_OBJECT_H_

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"

namespace omniscia::renderer {
    class Shader {
        u32 shaderProgram;

        std::string load_from_file(std::string path);

        u32 vertexShaderTmp;
        u32 fragmentShaderTmp;

        public:
            i32 try_compile(std::string vertSourcePath, std::string fragSourcePath);

            void compile();

            void activate();

            void terminate();

            void set_uniform_f32(const char *uniform, f32 value);
            void set_uniform_i32(const char *uniform, i32 value);
    };
}

#endif