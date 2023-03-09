#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "properties.h"
#include "renderer.h"
#include "sprite.h"
#include "frame_buffer.h"
#include "texture_manager.h"
#include "render_stage.h"

#include <iostream>

#include <cmath>

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

    using namespace omniscia::renderer::sprite;
    TextureManager::add_asset("assets/texture.png", "factorio_girl_texture");
    TextureManager::add_asset("assets/jojo_texture.png", "jojo_texture");
    
    TextureManager::load_assets();

    Sprite sprite1("jojo_texture", Vec3f{0.5f, 0.5f, 1.0f});
    Sprite sprite2("factorio_girl_texture");

    ShaderManager shaderManager;
    shaderManager.add_asset("assets/shaders/frag_stage_1.glsl", "frag_stage_1", FRAGMENT_SHADER);
    shaderManager.add_asset("assets/shaders/frag_stage_2.glsl", "frag_stage_2", FRAGMENT_SHADER);
    shaderManager.add_asset("assets/shaders/frag_stage_3.glsl", "frag_stage_3", FRAGMENT_SHADER);
    shaderManager.add_asset("assets/shaders/vert_stage_1.glsl", "vert_stage_1", VERTEX_SHADER);
    shaderManager.add_asset("assets/shaders/vert_stage_2.glsl", "vert_stage_2", VERTEX_SHADER);
    shaderManager.add_asset("assets/shaders/vert_stage_3.glsl", "vert_stage_3", VERTEX_SHADER);

    Shader shader1("vert_stage_1", "frag_stage_1");
    Shader shader2("vert_stage_2", "frag_stage_2");
    Shader shader3("vert_stage_3", "frag_stage_3");

    if(shader1.try_compile()) shader1.compile();
    if(shader2.try_compile()) shader2.compile();
    if(shader3.try_compile()) shader3.compile();

    RenderStage renderStage1;
        renderStage1.bind_target_texture_buffer(new TextureBuffer(600, 600));
        renderStage1.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
        renderStage1.bind_default_shader(&shader1);

    RenderStage renderStage2;
        renderStage2.bind_target_texture_buffer(new TextureBuffer(600, 600));
        renderStage2.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
        renderStage2.bind_default_shader(&shader2);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        
        renderStage1.render_stage_lambda([&](){ 
            sprite1.draw();
        });
        
        renderStage2.render_stage_lambda([&](){ 
            sprite2.draw();
            renderStage1.present_as_texture();
        });
        
        RenderStage::render_anonymous_stage_lambda([&]() {
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 1.0});
            shader3.activate();
            renderStage2.present_as_texture();
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDisable(GL_BLEND);

    shader2.terminate();

    glfwTerminate();
    return 0;
}
