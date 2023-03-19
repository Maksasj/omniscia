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

    //glfwSwapInterval(1);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer::loadGL();

    return 0;
}

int omniscia::Game::run() {
    using namespace omniscia::renderer::sprite;

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.2, 0.2}, {0.0, 0.6}, 5, true, 6}), "player-run-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.2, 0.2}, {0.0, 0.8}, 3, true, 24}), "player-idle-animation");
    //AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.2, 0.2}, {0.0, 0.4}, 3, true, 6}), "player-jump-animation");

    TextureManager::get_instance().add_asset("assets/texture.png", "factorio_girl_texture");
    TextureManager::get_instance().add_asset("assets/jojo_texture.png", "jojo_texture");
    TextureManager::get_instance().add_asset("assets/player.png", "player");
    TextureManager::get_instance().add_asset("assets/player-spritesheet.png", "player-spritesheet");

    TextureManager::get_instance().load_assets();

    //Spritesheet::get_instance().add_asset("player-spritesheet", "player_run", Vec2i);

    Sprite sprite1("factorio_girl_texture");

    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_1.glsl", "frag_stage_1", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_2.glsl", "frag_stage_2", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/frag_stage_3.glsl", "frag_stage_3", FRAGMENT_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_1.glsl", "vert_stage_1", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_2.glsl", "vert_stage_2", VERTEX_SHADER);
    ShaderManager::get_instance().add_asset("assets/shaders/vert_stage_3.glsl", "vert_stage_3", VERTEX_SHADER);

    Shader shader1("vert_stage_1", "frag_stage_1");
    Shader shader2("vert_stage_2", "frag_stage_2");
    Shader shader3("vert_stage_3", "frag_stage_3");

    if(shader1.try_compile()) shader1.compile();
    if(shader2.try_compile()) shader2.compile();
    if(shader3.try_compile()) shader3.compile();

    RenderStage renderStage1;
    renderStage1.bind_target_texture_buffer(new TextureBuffer(Properties::screen_width, Properties::screen_height));
    renderStage1.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
    renderStage1.bind_default_shader(&shader1);

    RenderStage renderStage2;
    renderStage2.bind_target_texture_buffer(new TextureBuffer(Properties::screen_width, Properties::screen_height));
    renderStage2.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
    renderStage2.bind_default_shader(&shader2);

    struct Level {
        Player player;
        //std::array<Entity, 1000> entities;
        std::vector<Entity> entities;

        Level clone() {
            //return {};
            return {player.clone(), entities};
        }
    } level;

    //Level active;
    std::deque<Level> timeLine;
    
    for(int i = 0; i < 1; ++i) {
        Entity wall = Entity();
        wall.add(new ECS_Positioned({0.0, -0.7}));
        wall.add(new ECS_Scaled({1.0, 0.25}, wall));
        wall.add(new ECS_SpriteRenderer("factorio_girl_texture", wall, 0));
        wall.add(new ECS_AABBCollider(wall));
        level.entities.push_back(wall);
    }

    /* Components binded twise, because of this we need to time sync imideialty */
    ECS_SpriteSheetRendererSystem::get_instance().time_sync();
    ECS_SpriteRendererSystem::get_instance().time_sync();
    ECS_PlayerControllerSystem::get_instance().time_sync();
    ECS_SpriteAnimationSystem::get_instance().time_sync();
    ECS_AABBColliderSystem::get_instance().time_sync();
    ECS_2DPhysicsRigidbodySystem::get_instance().time_sync();
    ECS_GravitySystem::get_instance().time_sync();

    level.player.time_sync();
    for(auto &p : level.entities) {
        p.time_sync();
    }
    /* ======================================================================== */
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    u64 frame = 0;
    while (!glfwWindowShouldClose(window)) {   
        Time::get_instance().update_delta_time_clock();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        ++frame;

        if(glfwGetKey(window, 'C') == GLFW_PRESS) {
            if(shader1.try_compile()) shader1.compile();
        }

        Controls::handle_input(window);
        
        static f32 timeLineManipulationTime = 0;
        if(frame % 5 == 0) {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            if(!Controls::get(PlayerController::TIME_JUMP)) {
                if(timeLine.size() > 0) {
                    level = timeLine[timeLine.size() - 1];
                    timeLine.pop_back();

                    ECS_SpriteSheetRendererSystem::get_instance().time_sync();
                    ECS_SpriteRendererSystem::get_instance().time_sync();
                    ECS_PlayerControllerSystem::get_instance().time_sync();
                    ECS_SpriteAnimationSystem::get_instance().time_sync();
                    ECS_AABBColliderSystem::get_instance().time_sync();
                    ECS_2DPhysicsRigidbodySystem::get_instance().time_sync();
                    ECS_GravitySystem::get_instance().time_sync();

                    level.player.time_sync();

                    for(auto &p : level.entities) {
                        p.time_sync();
                    }
                }
            } else {
                timeLine.push_back(level.clone());

                if(timeLine.size() >= 5000) {
                    timeLine.pop_front();
                }
            }

            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            timeLineManipulationTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000.0;
        }


        Time::run_every_n_milliseconds<16u>([]() {
            ECS_SpriteAnimationSystem::get_instance().update();
        });

        renderStage1.render_stage_lambda([&](){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            
            shader1.set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            ECS_SpriteRendererSystem::get_instance().render(&shader1);
            ECS_SpriteSheetRendererSystem::get_instance().render(&shader1);
            
            ECS_PlayerControllerSystem::get_instance().update();
            
            ECS_GravitySystem::get_instance().update();
            ECS_2DPhysicsRigidbodySystem::get_instance().update();
            ECS_AABBColliderSystem::get_instance().update();
            ECS_2DPhysicsRigidbodySystem::get_instance().late_update();
        });
        
        renderStage2.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);
            renderStage1.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
        });

        /* screen buffer */
        RenderStage::render_anonymous_stage_lambda([&]() {
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 1.0});
            shader3.activate();
            shader3.set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            renderStage2.present_as_texture();
        });


        /* ImGui */
        {
            ImGuiWindowFlags window_flags = 
                ImGuiWindowFlags_NoDecoration | 
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_AlwaysAutoResize | 
                ImGuiWindowFlags_NoSavedSettings | 
                ImGuiWindowFlags_NoFocusOnAppearing | 
                ImGuiWindowFlags_NoNav;

            ImGui::SetNextWindowPos({10.0f, 10.0f}, 0, {0.0f, 0.0f});
            ImGui::SetNextWindowBgAlpha(0.35f);
            if (ImGui::Begin("Example: Simple overlay", nullptr, window_flags)) {
                
                ImGui::Text("Frames buffered %llu / %llu", timeLine.size(), (u64)5000);
                ImGui::Text("Time manipulation time %f [ms]", timeLineManipulationTime);
                ImGui::Separator();

                ImGui::Text("Application average %.3f [ms/frame] (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::Separator();

                if (ImGui::IsMousePosValid())
                    ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
                else
                    ImGui::Text("Mouse Position: <invalid>");

                ImGui::End();
            }
        }

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
