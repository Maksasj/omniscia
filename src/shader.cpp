#include "shader.h"

omniscia::renderer::Shader::Shader(const std::string& shaderVertId, const std::string& shaderFragId) {
    using namespace omniscia::core;
    
    _shaderAssetVertex = ShaderManager::get_instance().get(shaderVertId);
    _shaderAssetFragment = ShaderManager::get_instance().get(shaderFragId);
}


std::string omniscia::renderer::Shader::load_from_file(std::string path) {
    std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

i32 omniscia::renderer::Shader::try_compile() {
    //std::cout << _shaderAssetVertex->get_file_path() << "\n";
    //std::cout << _shaderAssetFragment->get_file_path() << "\n";

    std::string vertSource = load_from_file(_shaderAssetVertex->get_file_path());
    const char* vertexShaderSource = vertSource.c_str();

    std::string fragSource = load_from_file(_shaderAssetFragment->get_file_path());
    const char* fragmentShaderSource = fragSource.c_str();

    _vertexShaderTmp = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexShaderTmp, 1, &vertexShaderSource, NULL);
    glCompileShader(_vertexShaderTmp);

    i32 success;
    char infoLog[512];
    glGetShaderiv(_vertexShaderTmp, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_vertexShaderTmp, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    // fragment shader
    _fragmentShaderTmp = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentShaderTmp, 1, &fragmentShaderSource, NULL);
    glCompileShader(_fragmentShaderTmp);
    // check for shader compile errors
    glGetShaderiv(_fragmentShaderTmp, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_fragmentShaderTmp, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return 1;
}

void omniscia::renderer::Shader::compile() {
    i32 success;
    char infoLog[512];

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertexShaderTmp);
    glAttachShader(_shaderProgram, _fragmentShaderTmp);
    glLinkProgram(_shaderProgram);
    // check for linking errors
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(_vertexShaderTmp);
    glDeleteShader(_fragmentShaderTmp);
}

void omniscia::renderer::Shader::activate() {
    glUseProgram(_shaderProgram);
}

void omniscia::renderer::Shader::terminate() {
    glDeleteProgram(_shaderProgram);
}

void omniscia::renderer::Shader::set_uniform_f32(const char *uniform, f32 value) const {
    i32 vertexColorLocation = glGetUniformLocation(_shaderProgram, uniform);
    glUseProgram(_shaderProgram);
    glUniform1f(vertexColorLocation, value);
}

void omniscia::renderer::Shader::set_uniform_i32(const char *uniform, i32 value) const {
    i32 vertexColorLocation = glGetUniformLocation(_shaderProgram, uniform);
    glUseProgram(_shaderProgram);
    glUniform1i(vertexColorLocation, value);
}

void omniscia::renderer::Shader::set_uniform_vec2f(const char *uniform, Vec2f value) const {
    i32 vertexColorLocation = glGetUniformLocation(_shaderProgram, uniform);
    glUseProgram(_shaderProgram);
    glUniform2f(vertexColorLocation, value.x, value.y);
}

void omniscia::renderer::Shader::set_uniform_vec2i(const char *uniform, Vec2i value) const {
    i32 vertexColorLocation = glGetUniformLocation(_shaderProgram, uniform);
    glUseProgram(_shaderProgram);
    glUniform2i(vertexColorLocation, value.x, value.y);
}

void omniscia::renderer::Shader::set_uniform_vec3f(const char *uniform, Vec3f value) const {
    i32 vertexColorLocation = glGetUniformLocation(_shaderProgram, uniform);
    glUseProgram(_shaderProgram);
    glUniform3f(vertexColorLocation, value.x, value.y, value.z);
}

void omniscia::renderer::Shader::set_uniform_vec3i(const char *uniform, Vec3i value) const {
    i32 vertexColorLocation = glGetUniformLocation(_shaderProgram, uniform);
    glUseProgram(_shaderProgram);
    glUniform3i(vertexColorLocation, value.x, value.y, value.z);
}
