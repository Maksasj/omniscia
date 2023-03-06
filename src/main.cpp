#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bufferObjects.h"
#include "shader.h"
#include "properties.h"
#include "renderer.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height);
void processInput(GLFWwindow *window);

int main() {
    using namespace omniscia::core;
    using namespace omniscia::renderer;

    Renderer::init();

    GLFWwindow* window = glfwCreateWindow(
        Properties::screen_width, 
        Properties::screen_height, 
        "Omniscia", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer::loadGL();

    Shader shader;

    if(shader.try_compile("assets/vert.glsl", "assets/frag.glsl")) {
        shader.compile();    
    }

    BufferObject obb;
    obb.initBuffers();




    u32 texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    i32 width, height, nrChannels;
    
    u8 *data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);




    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            if(shader.try_compile("assets/vert.glsl", "assets/frag.glsl")) {
                shader.compile();    
            } else {
                std::cout << "Error could not compile shader\n";
            }
        }

        glBindTexture(GL_TEXTURE_2D, texture);

        static f64 value = 0;
        ++value;
        shader.set_uniform_f32("tmp_uniform", (sin((value / 100.0)) + 1.0 / 2.0));
        shader.activate();
        
        obb.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    shader.terminate();

    glfwTerminate();
    return 0;
}

/*
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
*/
