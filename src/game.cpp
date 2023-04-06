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
    glfwSwapInterval(0);

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer::loadGL();

    return 0;
}

int omniscia::Game::run() {
    using namespace omniscia::gfx::sprite;

    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.125}, {0.0, 0.75}, 7, true, 5}), "player-run-animation");
    AnimationManager::get_instance().add_asset(AnimationAsset({{1.0, 1.0}, {0.125, 0.125}, {0.0, 0.875}, 7, true, 12}), "player-idle-animation");

    TextureManager::get_instance().load_assets();

    Sprite beachBackgroundBeachLayer("background_beach_beach_layer");
    Sprite beachBackgroundGrassOverlayLayer("background_beach_grass_overlay_layer");
    Sprite beachBackgroundSky1Layer("background_beach_sky1_layer");
    Sprite beachBackgroundSky2Layer("background_beach_sky2_layer");
    Sprite beachBackgroundTerrainLayer("background_beach_terrain_layer");

    Shader shader1("vert_stage_1", "frag_stage_1");
    Shader shader2("vert_stage_2", "frag_stage_2");
    Shader shader3("vert_stage_3", "frag_stage_3");
    Shader shaderBackground("vert_stage_background", "frag_stage_background");

    if(shader1.try_compile()) shader1.compile();
    if(shader2.try_compile()) shader2.compile();
    if(shader3.try_compile()) shader3.compile();
    if(shaderBackground.try_compile()) shaderBackground.compile();
    
    RenderStage renderBackgroundStage;
    renderBackgroundStage.bind_target_texture_buffer(new TextureBuffer(Properties::screen_width, Properties::screen_height));
    renderBackgroundStage.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
    renderBackgroundStage.bind_default_shader(&shaderBackground);

    RenderStage renderStage1;
    renderStage1.bind_target_texture_buffer(new TextureBuffer(Properties::screen_width, Properties::screen_height));
    renderStage1.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
    renderStage1.bind_default_shader(&shader1);

    RenderStage renderStage2;
    renderStage2.bind_target_texture_buffer(new TextureBuffer(Properties::screen_width, Properties::screen_height));
    renderStage2.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
    renderStage2.bind_default_shader(&shader2);

    Level level;
    LevelLoader::get_instance().load_level(level);

    std::deque<Level::LevelDynamic> timeLine;

    DebugUI::get_instance().get_metrics()._timeMaxLineLength = 5000;

    // for(int i = 0; i < 2; ++i) {
    //     Entity wall = Entity();
    //     wall.add<ECS_Positioned>(2.5f*i, -0.7f + -i*0.5f);
    //     wall.add<ECS_Scaled>(1.0, 0.25);
    //     wall.add<ECS_SpriteRenderer>("factorio_girl_texture", 0);
    //     wall.add<ECS_BoxColliderMesh>(Vec2f{1.0f, 1.0f}, Vec2f{1.0f, 1.0f});
    //     wall.add<ECS_AABBCollider>();
    //     level.staticPart.staticEntities.push_back(wall);
    // }

    /*
    {
        Entity wall = Entity();
        wall.add<ECS_Positioned>(0.0f, 0.0f);
        wall.add<ECS_Scaled>(0.1, 0.1);
        
        RawMeshDataBuilder builder;

        for(auto x = -2; x < 2; ++x)
            for(auto y = -2; y < 2; ++y)
                builder.append(BuildInMeshData::QUAD_MESH_DATA, {x * 2.0f,y * 2.0f});
        
        auto aa = builder.get();

        wall.add<ECS_TilemapRenderer>(aa, "factorio_girl_texture", 0);

        level.staticPart.staticEntities.push_back(wall);
    }
    */


    /* Components binded twise, because of this we need to time sync imideialty */
    level.time_sync();
    /* ======================================================================== */
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* ImGui */
    DebugUI::get_instance().init(window);

    u64 frame = 0;
    Time::get_instance().update_delta_time_clock();
    while (!glfwWindowShouldClose(window)) {   
        Time::get_instance().update_delta_time_clock();

        ++frame;

        if(glfwGetKey(window, 'C') == GLFW_PRESS) {
            if(shader1.try_compile()) shader1.compile();
        }

        Controls::handle_input(window);
        
        bool isTimeJump = false;
        static f32 timeLineManipulationTime = 0;
        if(!Controls::get(PlayerController::TIME_JUMP)) {
            //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            if(frame % 5 == 0) {
                if(timeLine.size() > 0) {
                    level.dynamicPart = timeLine[timeLine.size() - 1];
                    timeLine.pop_back();
                    level.time_sync();
                }
            }

            isTimeJump = true;
            //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            //timeLineManipulationTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000.0;
        } else {
            if(frame % 5 == 0) {
                timeLine.push_back(level.clone());

                if(timeLine.size() >= 5000) {
                    timeLine.pop_front();
                }
            }
        }

        if(!isTimeJump) {
            Time::run_every_n_milliseconds<16u>([]() {
                ECS_SpriteAnimationSystem::get_instance().update();
            });
        }

        ECS_CameraFollowSystem::get_instance().update(&shader1);
        ECS_PlayerDebugMetricsSystem::get_instance().update();

        if(!isTimeJump) {
            ECS_GravitySystem::get_instance().update();
            ECS_2DPhysicsRigidbodySystem::get_instance().update();
            ECS_AABBColliderSystem::get_instance().update();
            ECS_2DPhysicsRigidbodySystem::get_instance().late_update();
            ECS_PlayerControllerSystem::get_instance().update();
            ECS_PlayerJumpSystem::get_instance().update(); /* Need to be between collider updates, since should know is player standing */
            ECS_AABBColliderSystem::get_instance().reset();
        }

        /* Render background */
        renderBackgroundStage.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            f32 dt = Time::get_instance().get_delta_time();
            Vec2f playerPos = DebugUI::get_instance().get_metrics()._playerPos;
            playerPos /= 500.0f;

            static f32 clouds = 0.0f;
            clouds += dt;

            stage_shader->set_uniform_f32("layerOffset", (clouds / 100000.0f));
            beachBackgroundSky1Layer.render(stage_shader);

            stage_shader->set_uniform_f32("layerOffset", 2.0f * (clouds / 100000.0f));
            beachBackgroundSky2Layer.render(stage_shader);

            stage_shader->set_uniform_f32("layerOffset", playerPos.x * 10.5f);
            beachBackgroundBeachLayer.render(stage_shader);

            stage_shader->set_uniform_f32("layerOffset", playerPos.x * 21.0f);
            beachBackgroundTerrainLayer.render(stage_shader);
        });

        renderStage1.render_stage_lambda([&](){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 0.0, 0.0});

            shader1.set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            ECS_TilemapRendererSystem::get_instance().render(&shader1);
            ECS_SpriteRendererSystem::get_instance().render(&shader1);
            ECS_SpriteSheetRendererSystem::get_instance().render(&shader1);
        });

        renderStage2.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            renderBackgroundStage.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
            renderStage1.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
        });

        renderBackgroundStage.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            f32 dt = Time::get_instance().get_delta_time();
            Vec2f playerPos = DebugUI::get_instance().get_metrics()._playerPos;
            playerPos /= 500.0f;

            stage_shader->set_uniform_f32("layerOffset", playerPos.x * 100.0f);
            beachBackgroundGrassOverlayLayer.render(stage_shader);
        });

        /* screen buffer */
        RenderStage::render_anonymous_stage_lambda([&]() {
            Renderer::clearBuffer(Vec4f{0.0, 0.0, 1.0, 1.0});
            shader3.activate();
            shader3.set_uniform_f32("screen_aspect", (Properties::screen_width) / (float) Properties::screen_height);

            renderStage2.present_as_texture();
            renderBackgroundStage.present_as_texture();
        });

        DebugUI::get_instance().get_metrics()._timeCurrentLineLength = timeLine.size();
        DebugUI::get_instance().get_metrics()._timeManipulationTime = timeLineManipulationTime;
        DebugUI::get_instance().render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDisable(GL_BLEND);

    shader1.terminate();
    shader2.terminate();
    shader3.terminate();

    glfwTerminate();

    return 0;
}
