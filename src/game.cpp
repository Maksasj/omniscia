#include "game.h"

void window_size_callback(GLFWwindow* window, int width, int height) {
    using namespace omniscia;
    using namespace omniscia::gfx;
    using namespace omniscia::gfx::monitor;

    glfwSetWindowAspectRatio(window, 16, 9);

    Properties::get_instance().screenWidth = width;
    Properties::get_instance().screenHeight = height;
}

void omniscia::Game::load() {
    using namespace omniscia;
    using namespace omniscia::gfx;
    using namespace omniscia::gfx::monitor;

    Renderer::init();

    auto monitors = Monitor::retrieve_monitors();
    //monitors[1]->set_active();
    //monitors[0]->set_active();
    
    window = glfwCreateWindow(Properties::get_instance().screenWidth, Properties::get_instance().screenHeight, "Omniscia", NULL, NULL);
    //window = glfwCreateWindow(Properties::get_instance().screenWidth, Properties::get_instance().screenHeight, "Omniscia", Monitor::get_active()->get_glfw_monitor(), NULL);

    glfwSetWindowSizeCallback(window, window_size_callback);

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

    Shader backgroundStageShader("vert_stage_background", "frag_stage_background");
    Shader mainStageShader("vert_stage_main", "frag_stage_main");
    Shader intermediateStageShader("vert_stage_intermediate", "frag_stage_intermediate");
    Shader lateStageShader("vert_stage_late", "frag_stage_late");
    Shader finalStageShader("vert_stage_final", "frag_stage_final");
    Shader guiStageShader("vert_stage_gui", "frag_stage_gui");

    Shader transitionStageShader("vert_stage_transition", "frag_stage_transition");

    Sprite randomsprite("jojo_texture");

    try {
        backgroundStageShader.try_compile();
        backgroundStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    try {
        mainStageShader.try_compile();
        mainStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    try {
        intermediateStageShader.try_compile();
        intermediateStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    try {
        lateStageShader.try_compile();
        lateStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    try {
        finalStageShader.try_compile();
        finalStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    try {
        guiStageShader.try_compile();
        guiStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    try {
        transitionStageShader.try_compile();
        transitionStageShader.compile();
    } catch (const Shader::ShaderVertexException& exception) {
        std::cout << exception.what() << "\n";
    } catch (const Shader::ShaderFragmentException& exception) {
        std::cout << exception.what() << "\n";
    } catch (...) {
        std::cout << "Undefined exception\n";
    }

    RenderStage& renderBackgroundStage = RenderStagePool::get_instance().add_stage("BackgroundStage")
        .bind_target_texture_buffer(new TextureBuffer(256, 144))
        .bind_viewport_size(Vec4f(0.0, 0.0, 256.0, 144.0))
        .bind_default_shader(&backgroundStageShader)
        .bind_target_mesh(SpriteMesh(BuildInMeshData::QUAD_MESH_DATA))
        .bind_shader_uniform([](const Shader* shader) {
            shader->set_uniform_f32("screenAspect", 256.0 / 144.0);
            shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            shader->set_uniform_f32("cameraZoom", Camera::get_instance().get_zoom());
        })
        .bind_default_buffer_clear(Vec4f(1.0f, 1.0f, 1.0f, 0.0f));

    RenderStage& renderMainStage = RenderStagePool::get_instance().add_stage("MainStage")
        .bind_target_texture_buffer(new TextureBuffer(Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_viewport_size(Vec4f(0.0, 0.0, Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_default_shader(&mainStageShader)
        .bind_target_mesh(SpriteMesh(BuildInMeshData::QUAD_MESH_DATA))
        .bind_shader_uniform([](const Shader* shader) {
            shader->set_uniform_f32("screenAspect", (Properties::get_instance().screenWidth) / (float) Properties::get_instance().screenHeight);
            shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            shader->set_uniform_f32("cameraZoom", Camera::get_instance().get_zoom());
        })
        .bind_default_buffer_clear(Vec4f(1.0f, 1.0f, 1.0f, 0.0f));

    RenderStage& renderGuiStage = RenderStagePool::get_instance().add_stage("GuiStage")
        .bind_target_texture_buffer(new TextureBuffer(Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_viewport_size(Vec4f(0.0, 0.0, Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_default_shader(&guiStageShader)
        .bind_target_mesh(SpriteMesh(BuildInMeshData::QUAD_MESH_DATA))
        .bind_shader_uniform([](const Shader* shader) {
            shader->set_uniform_f32("screenAspect", (Properties::get_instance().screenWidth) / (float) Properties::get_instance().screenHeight);
            shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            shader->set_uniform_f32("cameraZoom", Camera::get_instance().get_zoom());
        })
        .bind_default_buffer_clear(Vec4f(1.0f, 1.0f, 1.0f, 0.0f));

    RenderStage& renderIntermediateStage = RenderStagePool::get_instance().add_stage("IntermediateStage")
        .bind_target_texture_buffer(new TextureBuffer(Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_viewport_size(Vec4f(0.0, 0.0, Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_default_shader(&intermediateStageShader)
        .bind_target_mesh(SpriteMesh(BuildInMeshData::QUAD_MESH_DATA))
        .bind_shader_uniform([](const Shader* shader) {
            shader->set_uniform_f32("screenAspect", (Properties::get_instance().screenWidth) / (float) Properties::get_instance().screenHeight);
            shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            shader->set_uniform_f32("cameraZoom", Camera::get_instance().get_zoom());
        })
        .bind_default_buffer_clear(Vec4f(1.0f, 1.0f, 1.0f, 0.0f));

    RenderStage& renderLateStage = RenderStagePool::get_instance().add_stage("LateStage")
        .bind_target_texture_buffer(new TextureBuffer(Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_viewport_size(Vec4f(0.0, 0.0, Properties::get_instance().screenWidth, Properties::get_instance().screenHeight))
        .bind_default_shader(&lateStageShader)
        .bind_target_mesh(SpriteMesh(BuildInMeshData::QUAD_MESH_DATA))
        .bind_shader_uniform([](const Shader* shader) {
            shader->set_uniform_f32("screenAspect", (Properties::get_instance().screenWidth) / (float) Properties::get_instance().screenHeight);
            shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            shader->set_uniform_f32("cameraZoom", Camera::get_instance().get_zoom());
        })
        .bind_default_buffer_clear(Vec4f(1.0f, 1.0f, 1.0f, 0.0f));
    
    RenderStage& renderTransitionStage = RenderStagePool::get_instance().add_stage("TransitionStage")
        .bind_target_texture_buffer(new TextureBuffer(256, 144))
        .bind_viewport_size(Vec4f(0.0, 0.0, 256.0, 144.0))
        .bind_default_shader(&transitionStageShader)
        .bind_target_mesh(SpriteMesh(BuildInMeshData::QUAD_MESH_DATA))
        .bind_shader_uniform([](const Shader* shader) {
            shader->set_uniform_f32("screenAspect", (Properties::get_instance().screenWidth) / (float) Properties::get_instance().screenHeight);
            shader->set_uniform_vec3f("cameraPosition", Camera::get_instance().get_pos());
            shader->set_uniform_f32("cameraZoom", Camera::get_instance().get_zoom());
        })
        .bind_default_buffer_clear(Vec4f::splat(0.0f));

    Scene* scene = new GameScene();
    _scenes["game_scene"] = scene;

    Scene* mainMenuScene = new MainMenuScene();
    _scenes["main_menu_scene"] = mainMenuScene;

    Scene* chapterChooseMenuScene = new ChapterChooseMenuScene();
    _scenes["chapter_choose_menu_scene"] = chapterChooseMenuScene;

    Scene* settingsScene = new SettingsScene();
    _scenes["settings_scene"] = settingsScene;
    
    Scene* secretsScene = new SecretsScene();
    _scenes["secrets_scene"] = secretsScene;

    switch_scene("main_menu_scene");

    _cutscenes["transition_cutscene_to_chapter_choose_scene"] = new TransitionCutscene(&transitionStageShader, "chapter_choose_menu_scene");
    _cutscenes["transition_cutscene_to_game_scene"] = new TransitionCutscene(&transitionStageShader, "game_scene");
    _cutscenes["transition_cutscene_to_settings"] = new TransitionCutscene(&transitionStageShader, "settings_scene");
    _cutscenes["transition_cutscene_to_secrets"] = new TransitionCutscene(&transitionStageShader, "secrets_scene");
    _cutscenes["death_cutscene"] = new DeathCutscene(&transitionStageShader);
    _cutscenes["pause_cutscene"] = new PauseCutscene(&transitionStageShader);
    _cutscenes["star_collection_cutscene"] = new PlayerCollectStarCutscene(&transitionStageShader);
    _cutscenes["chapter_1_end_cutscene"] = new Chapter1EndCutscene(&transitionStageShader);
    _cutscenes["background_music_cutscene"] = new BackgroundMusicCutscene();

    start_cutscene("pause_cutscene"); // Endless cutscene
    start_cutscene("background_music_cutscene"); // Endless cutscene

    _cutscenes["test_dialogue_cutscene"] = new DialogueCutscene(&transitionStageShader, {
        DialogueStepData("player_test_icon", 1, "Hello, who you are ?"),
        DialogueStepData("grandpa_test_icon", -1, "I am a random old guy,  just staying there"),
        DialogueStepData("player_test_icon", 1, "Interesting, is there   any interesting thigs todo ?"),
        DialogueStepData("grandpa_test_icon", -1, "Lol, no. GET REKT"),
        DialogueStepData("player_test_icon", 1, "Bruh, you very cringy   old guy"),
        DialogueStepData("grandpa_test_icon", -1, "Lol."),
    });

    _cutscenes["scene_save_checkpoint_cutscene"] = new SaveCheckpointCutscene(&transitionStageShader);
    _cutscenes["scene_load_checkpoint_cutscene"] = new LoadCheckpointCutscene(&transitionStageShader);

    DebugInfo::get_instance().get_metrics()._timeMaxLineLength = 5000;

    /* ImGui */
    DebugInfo::get_instance().init(window);

    Time::get_instance().update_delta_time_clock();
    while (!glfwWindowShouldClose(window)) {   
        Time::get_instance().update_delta_time_clock();

        Controls::get_instance().handle_input(window);

        update_cutscenes();

        ECS_PlayerTimeJumpControllerSystem::get_instance().update();

        const auto& isTimeJump = DebugInfo::get_instance().get_metrics()._isTimeJump;

        Time::run_every_n_milliseconds<16u>([]() {
            ECS_SpriteAnimationSystem::get_instance().update();
        });

        ECS_CameraFollowSystem::get_instance().update();
        ECS_PlayerDebugMetricsSystem::get_instance().update();
        ECS_SoundEmitterSystem::get_instance().update();
        ECS_ButtonSystem::get_instance().update();
        
        ECS_GravitySystem::get_instance().update();
        ECS_2DPhysicsRigidbodySystem::get_instance().update();
        ECS_AABBColliderSystem::get_instance().update();
        ECS_InteractiveSystem::get_instance().update();
        ECS_2DPhysicsRigidbodySystem::get_instance().late_update();
        ECS_PlayerJumpSystem::get_instance().update(); /* Need to be between collider updates, since should know is player standing */
        ECS_PlayerControllerSystem::get_instance().update();
        ECS_StateMachineBaseSystem::get_instance().update();

        if(!isTimeJump) {
            ECS_DeadlySystem::get_instance().update();
        }
        
        ECS_AABBColliderSystem::get_instance().reset();
        
        /* Render background */
        renderBackgroundStage.render_stage_lambda([&](const Shader* stage_shader){ 
            ECS_ProRendererSystem::get_instance().render();
        });

        renderMainStage.render_stage_lambda([&](){ 
            ECS_ProRendererSystem::get_instance().render();
        });

        renderGuiStage.render_stage_lambda([&]() {
            ECS_ProRendererSystem::get_instance().render();
        });

        renderIntermediateStage.render_stage_lambda([&](const Shader* stage_shader){ 
            renderBackgroundStage.present_as_texture();
            renderMainStage.present_as_texture(stage_shader, Vec2f::splat(0.0f), 0);
            renderGuiStage.present_as_texture(stage_shader, Vec2f::splat(0.0f), 0);

            ECS_ProRendererSystem::get_instance().render();
        });

        renderTransitionStage.render_stage_lambda([&](const Shader* stage_shader){ 
            randomsprite.render(Shader::get_active());
        });

        renderLateStage.render_stage_lambda([&](const Shader* stage_shader){ 
            renderIntermediateStage.present_as_texture();
            renderTransitionStage.present_as_texture();

            ECS_ProRendererSystem::get_instance().render();
        });

        glViewport(0, 0, Properties::get_instance().screenWidth, Properties::get_instance().screenHeight);
        /* screen buffer */
        RenderStage::render_anonymous_stage_lambda([&]() {
            finalStageShader.activate();
            renderLateStage.present_as_texture();

            // randomsprite.render(&finalStageShader);

            if(DebugInfo::get_instance().get_metrics()._debugUIEnabled) {
                DebugInfo::get_instance().render();
            }

            static bool buttonPressed = false;
            const bool isDebugButtonPressed = Controls::get_instance().get(PlayerController::DEBUGUI);
            bool& toggled = DebugInfo::get_instance().get_metrics()._debugUIEnabled;

            if(isDebugButtonPressed && !buttonPressed) {
                toggled = !toggled;
                buttonPressed = true;
            } else if(!isDebugButtonPressed) {
                buttonPressed = false;
            }
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDisable(GL_BLEND);

    mainStageShader.terminate();
    intermediateStageShader.terminate();
    lateStageShader.terminate();

    glfwTerminate();
}

void omniscia::Game::switch_scene(const std::string& sceneId) {
    if(_activeScene != nullptr)
        _activeScene->unbind();
    
    _activeScene = _scenes[sceneId];
    _activeScene->time_sync();
}

void omniscia::Game::start_cutscene(const std::string& cutsceneId) {
    auto found = _cutscenes.find(cutsceneId);

    if(found == _cutscenes.end()) {
        std::cout << "Unable to find cutscene with key: " << cutsceneId << "\n";
        return;
    }

    Cutscene* _activeCutscene = (*found).second;
    _activeCutscene->start();
    _activeCutscenes.push_back(_activeCutscene);
}

void omniscia::Game::start_cutscene(Cutscene* cutscenePtr) {
    cutscenePtr->start();
    _activeCutscenes.push_back(cutscenePtr);
}

void omniscia::Game::update_cutscenes() {
    _activeCutscenes.erase(
        std::remove_if(_activeCutscenes.begin(), _activeCutscenes.end(), Predicate_CutsceneEnd()),
        _activeCutscenes.end());

    const i32 size = _activeCutscenes.size();
    
    for(i32 i = 0; i < size; ++i)
        _activeCutscenes[i]->update();
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

void omniscia::Game::save_dynamic_checkpoint() {
    if(_activeScene == nullptr) 
        return;
    
    _activeScene->save_checkpoint();
}

void omniscia::Game::load_dynamic_checkpoint() {
    if(_activeScene == nullptr) 
        return;
    
    _activeScene->load_checkpoint();
}