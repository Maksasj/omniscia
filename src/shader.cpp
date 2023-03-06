#include "shader.h"

std::string omniscia::renderer::Shader::load_from_file(std::string path) {
    std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

i32 omniscia::renderer::Shader::try_compile(std::string vertSourcePath, std::string fragSourcePath) {
    std::string vertSource = load_from_file(vertSourcePath);
    const char* vertexShaderSource = vertSource.c_str();

    std::string fragSource = load_from_file(fragSourcePath);
    const char* fragmentShaderSource = fragSource.c_str();

    vertexShaderTmp = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderTmp, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderTmp);
    // check for shader compile errors
    i32 success;
    char infoLog[512];
    glGetShaderiv(vertexShaderTmp, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderTmp, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    } else {
        std::cout << "Succesfully compiled shader \n";
    }

    // fragment shader
    fragmentShaderTmp = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderTmp, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderTmp);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderTmp, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderTmp, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    } else {
        std::cout << "Succesfully compiled shader \n";
    }

    return 1;
}

void omniscia::renderer::Shader::compile() {
    i32 success;
    char infoLog[512];

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderTmp);
    glAttachShader(shaderProgram, fragmentShaderTmp);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShaderTmp);
    glDeleteShader(fragmentShaderTmp);
}

void omniscia::renderer::Shader::activate() {
    glUseProgram(shaderProgram);
}

void omniscia::renderer::Shader::terminate() {
    glDeleteProgram(shaderProgram);
}

void omniscia::renderer::Shader::set_uniform_f32(const char *uniform, f32 value) {
    i32 vertexColorLocation = glGetUniformLocation(shaderProgram, uniform);
    glUseProgram(shaderProgram);
    glUniform1f(vertexColorLocation, value);
}

void omniscia::renderer::Shader::set_uniform_i32(const char *uniform, i32 value) {
    i32 vertexColorLocation = glGetUniformLocation(shaderProgram, uniform);
    glUseProgram(shaderProgram);
    glUniform1i(vertexColorLocation, value);
}
