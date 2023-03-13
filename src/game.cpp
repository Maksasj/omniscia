#include "game.h"

int omniscia::Game::load() {
    Renderer::init();

    window = glfwCreateWindow(
        Properties::screen_width, 
        Properties::screen_height, 
        "Omniscia", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer::loadGL();

    return 0;
}

int omniscia::Game::run() {
    using namespace omniscia::renderer::sprite;
    TextureManager::add_asset("assets/texture.png", "factorio_girl_texture");
    TextureManager::add_asset("assets/jojo_texture.png", "jojo_texture");
    TextureManager::load_assets();

    Sprite sprite1("jojo_texture");
    Sprite sprite2("factorio_girl_texture");

    ShaderManager::add_asset("assets/shaders/frag_stage_1.glsl", "frag_stage_1", FRAGMENT_SHADER);
    ShaderManager::add_asset("assets/shaders/frag_stage_2.glsl", "frag_stage_2", FRAGMENT_SHADER);
    ShaderManager::add_asset("assets/shaders/frag_stage_3.glsl", "frag_stage_3", FRAGMENT_SHADER);
    ShaderManager::add_asset("assets/shaders/vert_stage_1.glsl", "vert_stage_1", VERTEX_SHADER);
    ShaderManager::add_asset("assets/shaders/vert_stage_2.glsl", "vert_stage_2", VERTEX_SHADER);
    ShaderManager::add_asset("assets/shaders/vert_stage_3.glsl", "vert_stage_3", VERTEX_SHADER);

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

    Player player;
    player.update();
    std::cout << "1: "<< player.read() << "\n";

    Player another = player.clone<Player>();
    //another.update();
    //another.update();
    //another.update();
    std::cout << "2: "<< another.read() << "\n";
    std::cout << "3: "<< player.read() << "\n";
    //std::vector<Player> vec;

    while (!glfwWindowShouldClose(window)) {
        Controls::handle_input(window);
        static float f = 0;
        f += 0.01f;
        
        //pp.push_back(player);

        //player.update();
        //vec.push_back(player);

        renderStage1.render_stage_lambda([&](){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});

            sprite1.render(&shader1, Vec2f{0.0f, 0.0f}, f, Vec2f{0.5f, 0.5f});
        });
        
        renderStage2.render_stage_lambda([&](){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});

            sprite2.render(&shader2, Vec2f{0.0f, 0.0f}, -f*0.1);
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
