#include "game.h"

void omniscia::Game::load() {
    using namespace omniscia;
    using namespace omniscia::gfx;
    using namespace omniscia::gfx::monitor;

    Renderer::init();

    auto monitors = Monitor::retrieve_monitors();
    //monitors[1]->set_active();
    //monitors[0]->set_active();
    
    window = glfwCreateWindow(Properties::screenWidth, Properties::screenHeight, "Omniscia", NULL, NULL);
    //window = glfwCreateWindow(Properties::screenWidth, Properties::screenHeight, "Omniscia", Monitor::get_active()->get_glfw_monitor(), NULL);

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

    Shader transitionStageShader("vert_stage_transition", "frag_stage_transition");

    Sprite randomsprite("jojo_texture");

    if(backgroundStageShader.try_compile()) backgroundStageShader.compile();
    if(mainStageShader.try_compile()) mainStageShader.compile();
    if(intermediateStageShader.try_compile()) intermediateStageShader.compile();
    if(lateStageShader.try_compile()) lateStageShader.compile();
    if(finalStageShader.try_compile()) finalStageShader.compile();
    if(transitionStageShader.try_compile()) transitionStageShader.compile();

    RenderStage& renderBackgroundStage = RenderStagePool::get_instance().add_stage((RenderStageProp){
        ._stageName = "BackgroundStage",
        ._textureBuffer = new TextureBuffer(Properties::screenWidth, Properties::screenHeight),
        ._defaultShader = &backgroundStageShader,
        ._spriteMesh = SpriteMesh(BuildInMeshData::QUAD_MESH_DATA),
        ._shaderUniforms = {
            ._screenAspect = [](){ return (Properties::screenWidth) / (float) Properties::screenHeight; },
            ._cameraPosition = [](){ return Camera::get_instance().get_pos(); },
            ._cameraZoom = [](){ return Camera::get_instance().get_zoom(); },
        },
        ._buffer = {
            ._clearBufferColor = Vec4f{1.0f, 1.0f, 1.0f, 0.0f},
        }
    });

    RenderStage& renderMainStage = RenderStagePool::get_instance().add_stage((RenderStageProp){
        ._stageName = "MainStage",
        ._textureBuffer = new TextureBuffer(Properties::screenWidth, Properties::screenHeight),
        ._defaultShader = &mainStageShader,
        ._spriteMesh = SpriteMesh(BuildInMeshData::QUAD_MESH_DATA),
        ._shaderUniforms = {
            ._screenAspect = [](){ return (Properties::screenWidth) / (float) Properties::screenHeight; },
            ._cameraPosition = [](){ return Camera::get_instance().get_pos(); },
            ._cameraZoom = [](){ return Camera::get_instance().get_zoom(); },
        },
        ._buffer = {
            ._clearBufferColor = Vec4f{1.0f, 1.0f, 1.0f, 0.0f},
        }
    });

    RenderStage& renderIntermediateStage = RenderStagePool::get_instance().add_stage((RenderStageProp){
        ._stageName = "IntermediateStage",
        ._textureBuffer = new TextureBuffer(Properties::screenWidth, Properties::screenHeight),
        ._defaultShader = &intermediateStageShader,
        ._spriteMesh = SpriteMesh(BuildInMeshData::QUAD_MESH_DATA),
        ._shaderUniforms = {
            ._screenAspect = [](){ return (Properties::screenWidth) / (float) Properties::screenHeight; },
            ._cameraPosition = [](){ return Camera::get_instance().get_pos(); },
            ._cameraZoom = [](){ return Camera::get_instance().get_zoom(); },
        },
        ._buffer = {
            ._clearBufferColor = Vec4f{1.0f, 1.0f, 1.0f, 0.0f},
        }
    });

    RenderStage& renderLateStage = RenderStagePool::get_instance().add_stage((RenderStageProp){
        ._stageName = "LateStage",
        ._textureBuffer = new TextureBuffer(Properties::screenWidth, Properties::screenHeight),
        ._defaultShader = &lateStageShader,
        ._spriteMesh = SpriteMesh(BuildInMeshData::QUAD_MESH_DATA),
        ._shaderUniforms = {
            ._screenAspect = [](){ return (Properties::screenWidth) / (float) Properties::screenHeight; },
            ._cameraPosition = [](){ return Camera::get_instance().get_pos(); },
            ._cameraZoom = [](){ return Camera::get_instance().get_zoom(); },
        },
        ._buffer = {
            ._clearBufferColor = Vec4f{1.0f, 1.0f, 1.0f, 0.0f},
        }
    });

    RenderStage& renderTransitionStage = RenderStagePool::get_instance().add_stage((RenderStageProp){
        ._stageName = "TransitionStage",
        ._textureBuffer = new TextureBuffer(256u, 144u),
        ._defaultShader = &transitionStageShader,
        ._spriteMesh = SpriteMesh(BuildInMeshData::QUAD_MESH_DATA),
        ._shaderUniforms = {
            ._screenAspect = [](){ return 256u / (float) 144u; },
            ._cameraPosition = [](){ return Camera::get_instance().get_pos(); },
            ._cameraZoom = [](){ return Camera::get_instance().get_zoom(); },
        },
        ._buffer = {
            ._clearBufferColor = Vec4f{0.0f, 0.0f, 0.0f, 0.0f},
        }
    });

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
    
    _cutscenes["test_dialogue_cutscene"] = new DialogueCutscene(&transitionStageShader);

    Cutscene cutscene = {
        CE_Step{
            new CE_Event((CE_Prop){ 
                ._pauseBeforeStart = true,
                ._pauseTimeBeforeStart = 8.0f,
            })
        },
        CE_Step{
            new CE_DisableSystemEvent<ECS_PlayerControllerSystem>((CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_CameraFollowSystem>((CE_DisableSystemProp){}),
            /** TODO */ // Time sync
            //new CE_LetterBoxEvent((CE_LetterBoxProp){}),
            /** =====*/
            new CE_CameraMoveEvent((CE_CameraMoveProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 0.2f,
                    ._durationTime = 5.0f
                },

                ._startPosition = {0.0f, 0.3f, 0.0f},
                ._finishPosition = {1.0f, 1.0f, 0.f},

                ._shapingFunction = &smoothstep<Vec3f>,
            }),
            new CE_CameraZoomEvent((CE_CameraZoomProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 0.2f,
                    ._durationTime = 5.0f
                },

                ._startZoom = 1.0f,
                ._finishZoom = 0.1f,

                ._shapingFunction = &smoothstep<f32>,
            }),
        },
        CE_Step{
            new CE_CameraMoveEvent((CE_CameraMoveProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 0.2f,
                    ._durationTime = 5.0f
                },

                ._startPosition = {1.0f, 1.0f, 0.f},
                ._finishPosition = {0.0f, 0.3f, 0.0f},

                ._shapingFunction = &smoothstep<Vec3f>,
            }),
            new CE_CameraZoomEvent((CE_CameraZoomProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 0.2f,
                    ._durationTime = 5.0f
                },

                ._startZoom = 0.1f,
                ._finishZoom = 1.0f,

                ._shapingFunction = &smoothstep<f32>,
            }),
        },
        CE_Step{
            new CE_EnableSystemEvent<ECS_PlayerControllerSystem>((CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_CameraFollowSystem>((CE_EnableSystemProp){}),
        },
    };

    _cutscenes["test_cutscene"] = &cutscene;

    DebugUI::get_instance().get_metrics()._timeMaxLineLength = 5000;

    /* ImGui */
    DebugUI::get_instance().init(window);

    Time::get_instance().update_delta_time_clock();
    while (!glfwWindowShouldClose(window)) {   
        Time::get_instance().update_delta_time_clock();

        Controls::get_instance().handle_input(window);

        update_cutscenes();

        ECS_PlayerTimeJumpControllerSystem::get_instance().update();

        auto& isTimeJump = DebugUI::get_instance().get_metrics()._isTimeJump;
        if(!isTimeJump) {
            Time::run_every_n_milliseconds<16u>([]() {
                ECS_SpriteAnimationSystem::get_instance().update();
            });
        }

        ECS_CameraFollowSystem::get_instance().update();
        ECS_PlayerDebugMetricsSystem::get_instance().update();
        ECS_SoundEmitterSystem::get_instance().update();
        ECS_ButtonSystem::get_instance().update();

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
            ECS_ProRendererSystem::get_instance().render();
        });

        renderMainStage.render_stage_lambda([&](){ 
            ECS_ProRendererSystem::get_instance().render();
        });

        renderIntermediateStage.render_stage_lambda([&](const Shader* stage_shader){ 
            renderBackgroundStage.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);
            renderMainStage.present_as_texture(stage_shader, Vec2f{0.0f, 0.0f}, 0);

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

        /* screen buffer */
        RenderStage::render_anonymous_stage_lambda([&]() {
            finalStageShader.activate();
            renderLateStage.present_as_texture();
            
            DebugUI::get_instance().render();
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

void omniscia::Game::switch_scene(std::string sceneId) {
    if(_activeScene != nullptr)
        _activeScene->unbind();
    
    _activeScene = _scenes[sceneId];
    _activeScene->time_sync();
}

void omniscia::Game::start_cutscene(std::string cutsceneId) {
    Cutscene* _activeCutscene = _cutscenes[cutsceneId];
    _activeCutscene->start();
    _activeCutscenes.push_back(_activeCutscene);
}

void omniscia::Game::start_cutscene(Cutscene* cutscenePtr) {
    cutscenePtr->start();
    _activeCutscenes.push_back(cutscenePtr);
}

void omniscia::Game::update_cutscenes() {
    _activeCutscenes.erase(std::remove_if(_activeCutscenes.begin(), _activeCutscenes.end(), 
        [](Cutscene* cutscene) { 
            return cutscene->is_ended(); 
        }), _activeCutscenes.end());

    for(auto& cutscene : _activeCutscenes) {
        cutscene->update();
    }
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
