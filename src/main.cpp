#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "properties.h"
#include "renderer.h"
#include "sprite.h"
#include "frame_buffer.h"

#include <iostream>

#include <cmath>
// #include <fstream>
// #include <nlohmann/json.hpp>

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

    Shader shader1;
    Shader shader2;
    Shader shader3;

    if(shader1.try_compile("assets/shaders/vert_stage_1.glsl", "assets/shaders/frag_stage_1.glsl"))
        shader1.compile();    

    if(shader2.try_compile("assets/shaders/vert_stage_2.glsl", "assets/shaders/frag_stage_2.glsl"))
        shader2.compile();    

    if(shader3.try_compile("assets/shaders/vert_stage_3.glsl", "assets/shaders/frag_stage_3.glsl"))
        shader3.compile();   

    using namespace omniscia::renderer::sprite;
    Sprite sprite;

    FrameBuffer framebuffer1;
        framebuffer1.bind();
        TextureBuffer texture1(600, 600);
        framebuffer1.bind_target_texture_buffer(texture1);
    framebuffer1.unbind();

    FrameBuffer framebuffer2;
        framebuffer2.bind();
        TextureBuffer texture2(600, 600);
        framebuffer2.bind_target_texture_buffer(texture2);
    framebuffer2.unbind();

    while (!glfwWindowShouldClose(window)) {
        {
            framebuffer1.bind();
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
        
                shader1.activate();
                sprite.bind(); 

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            framebuffer1.unbind();
        }
        
        {
            framebuffer2.bind();
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
        
                shader2.activate();
                texture1.bind();

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            framebuffer2.unbind();
        }

        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader3.activate();
            texture2.bind();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader2.terminate();

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
