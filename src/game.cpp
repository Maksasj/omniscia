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

    //Sprite sprite1("jojo_texture");
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

    /* ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {   
        // Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        Controls::handle_input(window);

        player.update();

        renderStage1.render_stage_lambda([&](){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});

            player.render(&shader1);
        });
        
        renderStage2.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});

            sprite2.render(stage_shader, Vec2f{0.0f, 0.0f}, 0.1);
            renderStage1.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
        });

        /* screen buffer */
        RenderStage::render_anonymous_stage_lambda([&]() {
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 1.0});

            //ImGui_ImplOpenGL3_NewFrame();
            //ImGui_ImplGlfw_NewFrame();
            //ImGui::NewFrame();

            shader3.activate();
            renderStage2.present_as_texture();
        });



        //ImGui::Begin("Poggers");
        ImGui::ShowDemoWindow();
        //ImGui::End();

        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDisable(GL_BLEND);

    shader2.terminate();

    glfwTerminate();
    return 0;
}
