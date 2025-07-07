//     Universidade Federal do Rio Grande do Sul
//             Instituto de Informática
//       Departamento de Informática Aplicada
//
//    INF01047 Fundamentos de Computação Gráfica
//               Prof. Eduardo Gastal
//
//                 TRABALHO FINAL

// C++ headers
#include <iostream>

// GLM headers
#include <glm/gtc/type_ptr.hpp>

// Local headers
#include "camera.hpp"
#include "object_model.hpp"
#include "callbacks.hpp"
#include "gpu_functions.hpp"
#include "show_text.hpp"
#include "monkey.hpp"
#include "bloon.hpp"
#include "dart.hpp"
#include "player.hpp"
#include "collisions.hpp"

int main(int argc, char* argv[]){
    // initialize glfw
    int success = glfwInit();

    if(!success){
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // define error callback
    glfwSetErrorCallback(ErrorCallback);

    // OpenGL version 3.3 (or superior)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bloons 3D", NULL, NULL);

    if(!window){
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // define callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    // select render window
    glfwMakeContextCurrent(window);

    // load OpenGL functions
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // define framebuffer callback
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    FramebufferSizeCallback(window, SCREEN_WIDTH, SCREEN_HEIGHT);

    // // print GPU informations
    // const GLubyte *vendor      = glGetString(GL_VENDOR);
    // const GLubyte *renderer    = glGetString(GL_RENDERER);
    // const GLubyte *glversion   = glGetString(GL_VERSION);
    // const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    // printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    // load shaders
    LoadShadersFromFiles();

    // load textures
    LoadTextureImage("../../data/textures/map.png"); // 0
    LoadTextureImage("../../data/textures/red.png"); // 1
    LoadTextureImage("../../data/textures/blue.png"); // 2
    LoadTextureImage("../../data/textures/green.png"); // 3
    LoadTextureImage("../../data/textures/yellow.png"); // 4
    LoadTextureImage("../../data/textures/brown.png"); // 5
    LoadTextureImage("../../data/textures/monkey.png"); // 6
    LoadTextureImage("../../data/textures/metal.png"); // 7
    LoadTextureImage("../../data/textures/wall_front.png"); // 8
    LoadTextureImage("../../data/textures/wall_right.png"); // 9

    // load object models
    ObjectModel planeModel("../../data/models/plane.obj");
    planeModel.ComputeNormals();
    planeModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel bloonModel("../../data/models/bloon.obj");
    bloonModel.ComputeNormals();
    bloonModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel dartModel("../../data/models/dart.obj");
    dartModel.ComputeNormals();
    dartModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel monkeyLevel1Model("../../data/models/monkey_level_1.obj");
    monkeyLevel1Model.ComputeNormals();
    monkeyLevel1Model.BuildTrianglesAndAddToVirtualScene();

    ObjectModel monkeyLevel2Model("../../data/models/monkey_level_2.obj");
    monkeyLevel2Model.ComputeNormals();
    monkeyLevel2Model.BuildTrianglesAndAddToVirtualScene();

    if(argc > 1){
        ObjectModel model(argv[1]);
        model.BuildTrianglesAndAddToVirtualScene();
    }

    // initialize text rendering
    TextRendering_Init();

    // enable Z-buffer
    glEnable(GL_DEPTH_TEST);

    // enable backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // previous right mouse button state
    bool previousRightMouseButtonPressed = false;

    // start timers
    float currentTime = (float)glfwGetTime();

    float previousTimeCamera = currentTime;
    float previousTimeBloon = currentTime;
    float previousTimeDart = currentTime;
    float previousTimeMonkey = currentTime;

    float deltaTimeCamera;
    float deltaTimeBloon;
    float deltaTimeDart;
    float deltaTimeMonkey;

    // reset camera
    camera.reset(g_CameraTheta, g_CameraPhi, g_CameraDistance);

    // setup first round
    int round = 1;
    setupRound(round);

    // render window
    while(!glfwWindowShouldClose(window)){
        // define background color
        glClearColor(0.77f, 0.98f, 1.0f, 1.0f);

        // paint framebuffer pixels and reset Z-buffer pixels
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // select GPU program
        glUseProgram(g_GpuProgramID);

        // update camera
        camera.update(g_CameraTheta, g_CameraPhi, g_CameraDistance);

        // update time
        currentTime = (float)glfwGetTime();

        // update camera time
        deltaTimeCamera = currentTime - previousTimeCamera;
        previousTimeCamera = currentTime;

        // check camera control keys
        if(W_pressed)
            camera.move('F', deltaTimeCamera, monkeys); // front

        if(A_pressed)
            camera.move('L', deltaTimeCamera, monkeys); // left

        if(S_pressed)
            camera.move('B', deltaTimeCamera, monkeys); // back

        if(D_pressed)
            camera.move('R', deltaTimeCamera, monkeys); // right

        if(SPACE_pressed)
            camera.move('U', deltaTimeCamera, monkeys); // up

        if(SHIFT_pressed)
            camera.move('D', deltaTimeCamera, monkeys); // down

        // if(B_pressed){
        //     bloons[0].resetTime();
        // }

        // compute view matrix
        glm::mat4 view = Matrix_Camera_View(camera.getPosition(), camera.getViewVector(), camera.getUpVector());

        // compute projection matrix
        glm::mat4 projection;

        float nearplane = -0.1f;
        float farplane  = -50.0f;

        if(g_UsePerspectiveProjection){
            // perspective projection
            float field_of_view = 3.141592 / 3.0f;
            projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
        }
        else{
            // ortographic projection
            float t = 1.5f*g_CameraDistance/2.5f;
            float b = -t;
            float r = t*g_ScreenRatio;
            float l = -r;
            projection = Matrix_Orthographic(l, r, b, t, nearplane, farplane);
        }

        // send view and projection matrices to GPU
        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

        // create model matrix
        glm::mat4 model = Matrix_Identity();

        // draw ground
        model = Matrix_Scale(10.0f, 1.0f, 6.44f);

        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, PLANE);
        glUniform1i(g_shading_uniform, PHONG);

        DrawVirtualObject("plane");

        // draw walls
        model = Matrix_Translate(0.0f, 6.42f, -6.44f) *
                Matrix_Rotate_X(3.141592 / 2.0f) *
                Matrix_Scale(10.0f, 1.0f, 6.42f);

        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL_FRONT);
        glUniform1i(g_shading_uniform, PHONG);

        DrawVirtualObject("plane");

        model = Matrix_Translate(0.0f, 6.42f, 6.44f) *
                Matrix_Rotate_Z(3.141592) *
                Matrix_Rotate_X(-3.141592 / 2.0f) *
                Matrix_Scale(10.0f, 1.0f, 6.42f);

        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL_BACK);
        glUniform1i(g_shading_uniform, PHONG);

        DrawVirtualObject("plane");

        model = Matrix_Translate(10.0f, 6.44f, 0.0f) *
                Matrix_Rotate_Z(3.141592 / 2.0f) *
                Matrix_Scale(6.44f, 1.0f, 6.44f);

        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL_RIGHT);
        glUniform1i(g_shading_uniform, PHONG);

        DrawVirtualObject("plane");

        model = Matrix_Translate(-10.0f, 6.44f, 0.0f) *
                Matrix_Rotate_X(3.141592) *
                Matrix_Rotate_Z(-3.141592 / 2.0f) *
                Matrix_Scale(6.44f, 1.0f, 6.44f);

        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, WALL_LEFT);
        glUniform1i(g_shading_uniform, PHONG);

        DrawVirtualObject("plane");

        // update bloons time
        deltaTimeBloon = currentTime - previousTimeBloon;
        previousTimeBloon = currentTime;

        // updateBloons(deltaTimeBloon);

        // for each bloon...
        for(int i=0; i<int(bloons.size()); i++){
            if(bloons[i].isBlown())
                continue;

            // update
            bloons[i].updateTranslation(deltaTimeBloon);

            if(bloons[i].reachedEnd()){
                player.discountLife(1);
                bloons[i].blow();
            }

            // draw
            if(!bloons[i].isReady())
                continue;

            glm::vec3 translation = bloons[i].getTranslation();
            model = Matrix_Translate(translation.x, translation.y, translation.z);

            glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
            glUniform1i(g_object_id_uniform, bloons[i].getModelId());
            glUniform1i(g_shading_uniform, PHONG);
            glUniform1i(g_bloon_level, bloons[i].getLevel());

            DrawVirtualObject(bloons[i].getModelName());
        }

        // update monkeys time
        deltaTimeMonkey = currentTime - previousTimeMonkey;
        previousTimeMonkey = currentTime;

        // for each monkey...
        for(int i=0; i<int(monkeys.size()); i++){
            // update
            monkeys[i].updateCooldown(deltaTimeMonkey);

            if(monkeys[i].getCooldown() >= 3.0f){
                monkeys[i].setReady();
                monkeys[i].resetCooldown();
            }

            for(int j = 0; j < int(bloons.size()); j++){
                if(bloons[j].isBlown())
                    continue;

                if(is_point_in_range(bloons[j].getTranslation(), monkeys[i].getTranslation(), monkeys[i].getRange())){
                    monkeys[i].lookToBloon(bloons[j].getTranslation());
                    
                    if(monkeys[i].isReady()){
                        createDart(monkeys[i].getTranslation(), bloons[j].getTranslation(), j, i, monkeys[i].getRange());
                        monkeys[i].setNotReady();
                    }

                    break;
                }
            }   

            // draw
            glm::vec3 translation = monkeys[i].getTranslation();
            float rotation = monkeys[i].getRotation();

            model = Matrix_Translate(translation.x, translation.y, translation.z)
                * Matrix_Rotate_Y(rotation);

            glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
            glUniform1i(g_object_id_uniform, monkeys[i].getModelId());

            if(monkeys[i].getLevel() == 1)
                glUniform1i(g_shading_uniform, GOURAUD);
            else
                glUniform1i(g_shading_uniform, PHONG);

            DrawVirtualObject(monkeys[i].getModelName());         
        }

        // update darts time
        deltaTimeDart = currentTime - previousTimeDart;
        previousTimeDart = currentTime;

        // for each dart...
        for(int i = 0; i < int(darts.size()); i++){            
            if(darts[i].isAlive()){
                // update
                darts[i].setRotation();

                darts[i].updateDeltaPosition(deltaTimeDart);

                int b_idx = darts[i].getBloonTargetId();
                int m_idx = darts[i].getMonkeyId();

                glm::vec4 vec_t = bloons[b_idx].getTranslation();
                glm::mat4 mat_t = Matrix_Identity() * Matrix_Translate(vec_t.x, vec_t.y, vec_t.z);

                glm::vec4 bbox_t_max = mat_t * bloons[b_idx].getMaxBbox();
                glm::vec4 bbox_t_min = mat_t * bloons[b_idx].getMinBbox();

                if(is_ray_hit_bbox(bbox_t_min, bbox_t_max, darts[i].getPosition(), darts[i].getDeltaPosition())){
                    bloons[b_idx].loseLevel(monkeys[m_idx].getLevel());
                    darts[i].setNotAlive();

                    if(bloons[b_idx].isBlown())
                        player.giveMoney(5);
                }
                else{ 
                    darts[i].updatePosition();

                    if(!is_point_in_range(darts[i].getPosition(), darts[i].getInitialPosition(), darts[i].getRange())){
                        darts[i].setNotAlive();
                    }
                }

                // draw
                glm::vec4 translation = darts[i].getPosition();
                float rotation = darts[i].getRotation();

                model = Matrix_Translate(translation.x, translation.y, translation.z)
                    * Matrix_Rotate_Y(rotation);

                glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
                glUniform1i(g_object_id_uniform, darts[i].getModelId());
                glUniform1i(g_shading_uniform, PHONG);

                DrawVirtualObject(darts[i].getModelName());
            }
        }

        // place monkeys
        if((!previousRightMouseButtonPressed && g_RightMouseButtonPressed) && player.inStrategyMode() && player.canBuy(50)){

            float translation_x = ((g_LastCursorPosX / (SCREEN_WIDTH/2)) - 1) * 10.0;
            float translation_z = ((g_LastCursorPosY / (SCREEN_HEIGHT/2)) - 1) * 6.44;

            // printf("%f %f\n", translation_x, translation_z);

            if(monkeyPositionValid(translation_x, translation_z)){
                int idx = placeMonkey(translation_x, translation_z);

                if(idx == -1)
                    player.discountMoney(50);
                else if(player.canBuy(100)){
                    monkeys[idx].upgrade();
                    player.discountMoney(100);
                }
            }
        }

        // update right mouse button control
        previousRightMouseButtonPressed = g_RightMouseButtonPressed;

        if(roundFinished()){
            round += 1;
            setupRound(round);
            player.giveMoney(100);
        }

        if(player.lost()){
            break;
        }

        // // print projection matrix
        // TextRendering_ShowProjection(window);

        // print fps
        TextRendering_ShowFramesPerSecond(window);

        // print info
        PrintInfo(window, player.getLife(), player.getMoney());

        // swap buffers
        glfwSwapBuffers(window);

        // check for callbacks
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

// set makeprg=cd\ ..\ &&\ make\ run\ >/dev/null
// vim: set spell spelllang=pt_br :
