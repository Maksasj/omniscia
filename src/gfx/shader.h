/**
 * @file 
 * shader.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SHADER_H_
#define _SHADER_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include "shader_manager.h"
#include "shader_asset.h"
#include "types.tpp"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omniscia::core;

    /**
     * @brief Shader - class used for managing 
     * opengl shader, manages compilation, 
     * shader asset loading and etc.
    */
    class Shader {
        private:
            /** @brief Opengl program shader id */
            u32 _shaderProgram;

            /** @brief Temporary vertex shader id, used for runtime recompilation */
            u32 _vertexShaderTmp;
            
            /** @brief Temporary fragment shader id, used for runtime recompilation */
            u32 _fragmentShaderTmp;

            /** @brief Pointer to vertex shader asset */
            ShaderAsset* _shaderAssetVertex;
            
            /** @brief Pointer to fragment shader asset */
            ShaderAsset* _shaderAssetFragment;

            /** @brief Pointer to currently active shader */
            static Shader* _currentlyActiveShader;

            /**
             * @brief Loads content of the existing file into a string
             * 
             * @param path to the file that should be readed
             * @return string representing entire content of the provided file
            */
            static std::string load_from_file(std::string path);

        public:
            /**
             * @brief Default shader constructor
             * 
             * @param shaderVertId vertex shader id
             * @param shaderFragId fragment shader id
            */
            Shader(const std::string& shaderVertId, const std::string& shaderFragId);

            /**
             * @brief Function used to compile fragment 
             * and vertex shader, and stores it to 
             * temporary variable 
             * 
             * @return returns 0 is shader compilation failed
            */
            i32 try_compile();

            /**
             * @brief Used already compiled shader(by try_compile()) 
             * and assembles into opengl shader program
            */
            void compile();

            /** @brief Activates opengl shader program */
            void activate();

            /**
             * @brief Get currently active shader
             */
            static Shader* get_active();

            /**
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - f32 value which needed to be set to the uniform
            */
            void set_uniform_f32(const char *uniform, const f32& value) const;

            /**
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - i32 value which needed to be set to the uniform
            */
            void set_uniform_i32(const char *uniform, const i32& value) const;

            /** 
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - Vec2f value which needed to be set to the uniform
            */
            void set_uniform_vec2f(const char *uniform, const Vec2f& value) const;

            /** 
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - Vec2i value which needed to be set to the uniform
            */
            void set_uniform_vec2i(const char *uniform, const Vec2i& value) const;

            /** 
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - Vec3f value which needed to be set to the uniform
            */
            void set_uniform_vec3f(const char *uniform, const Vec3f& value) const;

            /** 
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - Vec3i value which needed to be set to the uniform
            */
            void set_uniform_vec3i(const char *uniform, const Vec3i& value) const;

            /** 
             * @brief Sets uniform value of the openg shader program to specific value  
             * 
             * @param uniform uniform name
             * @param value - Matrix<f32, 2, 2> value which needed to be set to the uniform
            */
            void set_uniform_mat2x2f(const char *uniform, const Matrix<f32, 2, 2>& value) const;

            /** @brief Terminates opengl shader program */
            void terminate();
    };
}

#endif