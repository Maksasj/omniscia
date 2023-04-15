#include "game.h"

void omniscia::Game::load() {
    Renderer::init();

    window = glfwCreateWindow(Properties::screenWidth, Properties::screenHeight, "Omniscia", NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    Renderer::load_gl();

    omniscia::core::SoundEngine::get_instance().initialize();
}

void omniscia::Game::run() {
    using namespace omniscia::gfx::sprite;
    TextureManager::get_instance().load_assets();
    SoundManager::get_instance().load_assets();

    Shader shader1("vert_stage_1", "frag_stage_1");
    Shader shader2("vert_stage_2", "frag_stage_2");
    Shader shader3("vert_stage_3", "frag_stage_3");
    Shader shaderBackground("vert_stage_background", "frag_stage_background");

    if(shader1.try_compile()) shader1.compile();
    if(shader2.try_compile()) shader2.compile();
    if(shader3.try_compile()) shader3.compile();
    if(shaderBackground.try_compile()) shaderBackground.compile();
    
    RenderStage renderBackgroundStage;
        renderBackgroundStage.bind_target_texture_buffer(new TextureBuffer(Properties::screenWidth, Properties::screenHeight));
        renderBackgroundStage.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
        renderBackgroundStage.bind_default_shader(&shaderBackground);

    RenderStage renderStage1;
        renderStage1.bind_target_texture_buffer(new TextureBuffer(Properties::screenWidth, Properties::screenHeight));
        renderStage1.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
        renderStage1.bind_default_shader(&shader1);

    RenderStage renderStage2;
        renderStage2.bind_target_texture_buffer(new TextureBuffer(Properties::screenWidth, Properties::screenHeight));
        renderStage2.bind_target_mesh(BuildInMeshData::QUAD_MESH_DATA);
        renderStage2.bind_default_shader(&shader2);

    Scene* scene = new Scene();
    SceneLoader::get_instance().load_scene(*scene);
    scene->add_dynamic_entity<Crab>();
    scene->add_dynamic_entity<Player>();
    scene->add_dynamic_entity<Grandpa>();
    scene->add_static_entity<BeachParallaxBackground>();
    scene->unbind();
    _scenes["game_scene"] = scene;

    Scene* anotherScene = new Scene();
    // anotherScene->add_dynamic_entity<Crab>();
    anotherScene->unbind();
    _scenes["another_scene"] = anotherScene;
    
    switch_scene("game_scene");

    Cutscene cutscene = {
        CE_Step{
            new CE_LogEvent((CE_LogProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 4.0f,

                    ._pauseAfterFinishing = true,
                    ._pauseTimeAfterFinishing = 8.0f,
                    
                    ._pauseBetweenRepeats = true,
                    ._pauseTimeBetweenRepeats = 2.0f,
                    ._timesToRepeat = 5,
                },

                ._message = "First Step, First Event",
            }),
            new CE_LogEvent((CE_LogProp){ 
                ._base = (CE_Prop){
                    ._timesToRepeat = 2,
                },

                ._message = "First Step, Second Event",
            })
        },
        CE_Step{
            new CE_LogEvent((CE_LogProp){ 
                ._base = (CE_Prop){
                    ._durationTime = 5.0f
                },

                ._message = "Second event",
            })
        },
    };

    cutscene.start();
    
    DebugUI::get_instance().get_metrics()._timeMaxLineLength = 5000;

    /* ImGui */
    DebugUI::get_instance().init(window);

    Time::get_instance().update_delta_time_clock();
    while (!glfwWindowShouldClose(window)) {   
        Time::get_instance().update_delta_time_clock();

        Controls::handle_input(window);
        cutscene.update();
        // std::cout << Time::get_time() << "\n";

        ECS_PlayerTimeJumpControllerSystem::get_instance().update();

        auto& isTimeJump = DebugUI::get_instance().get_metrics()._isTimeJump;
        if(!isTimeJump) {
            Time::run_every_n_milliseconds<16u>([]() {
                ECS_SpriteAnimationSystem::get_instance().update();
            });
        }

        ECS_CameraFollowSystem::get_instance().update(&shader1);
        ECS_PlayerDebugMetricsSystem::get_instance().update();
        ECS_SoundEmitterSystem::get_instance().update();

        if(!isTimeJump) {
            ECS_GravitySystem::get_instance().update();
            ECS_2DPhysicsRigidbodySystem::get_instance().update();
            ECS_AABBColliderSystem::get_instance().update();
            ECS_2DPhysicsRigidbodySystem::get_instance().late_update();
            ECS_PlayerControllerSystem::get_instance().update();
            ECS_PlayerJumpSystem::get_instance().update(); /* Need to be between collider updates, since should know is player standing */
            ECS_StateMachineBaseSystem::get_instance().update();
            ECS_AABBColliderSystem::get_instance().reset();
        }
        
        /* Render background */
        renderBackgroundStage.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clear_buffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screenAspect", (Properties::screenWidth) / (float) Properties::screenHeight);
            stage_shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            
            ECS_ParallaxSpriteRendererBackSystem::get_instance().render(stage_shader);
        });

        renderStage1.render_stage_lambda([&](){ 
            Renderer::clear_buffer(Vec4f{0.0, 0.0, 0.0, 0.0});
            shader1.set_uniform_f32("screenAspect", (Properties::screenWidth) / (float) Properties::screenHeight);
            shader1.set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());

            ECS_SpriteRendererSystem::get_instance().render(&shader1);
            ECS_SpriteSheetRendererSystem::get_instance().render(&shader1);
            ECS_TilemapRendererSystem::get_instance().render(&shader1);
        });

        renderStage2.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clear_buffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screenAspect", (Properties::screenWidth) / (float) Properties::screenHeight);
            stage_shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());

            renderBackgroundStage.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
            renderStage1.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
        });

        renderBackgroundStage.render_stage_lambda([&](const Shader* stage_shader){ 
            Renderer::clear_buffer(Vec4f{0.0, 0.0, 1.0, 0.0});
            stage_shader->set_uniform_f32("screenAspect", (Properties::screenWidth) / (float) Properties::screenHeight);
            stage_shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            
            ECS_ParallaxSpriteRendererFrontSystem::get_instance().render(stage_shader);
        });

        /* screen buffer */
        RenderStage::render_anonymous_stage_lambda([&]() {
            Renderer::clear_buffer(Vec4f{0.0, 0.0, 1.0, 1.0});
            shader3.activate();
            shader3.set_uniform_f32("screenAspect", (Properties::screenWidth) / (float) Properties::screenHeight);
            shader3.set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());

            renderStage2.present_as_texture();
            renderBackgroundStage.present_as_texture();
            DebugUI::get_instance().render();
        });

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
}

void omniscia::Game::switch_scene(std::string sceneId) {
    if(_activeScene != nullptr)
        _activeScene->unbind();
    
    _activeScene = _scenes[sceneId];
    _activeScene->time_sync();
}

void omniscia::Game::switch_scene(Scene* scenePtr) {
    if(_activeScene != nullptr)
        _activeScene->unbind();
    
    _activeScene = scenePtr;
    _activeScene->time_sync();
}

omniscia::Game& omniscia::Game::get_instance() {
    static Game game;
    return game;
}

omniscia::core::TimeLessNessContainer<omniscia::core::Scene::SceneDynamic, 5000>& omniscia::Game::ref_time_line() {
    return _timeLine;
}

omniscia::core::Scene* omniscia::Game::get_active_scene() {
    return _activeScene;
}
