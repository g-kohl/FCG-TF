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

    // print GPU informations
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    // load shaders
    LoadShadersFromFiles();

    // load textures
    LoadTextureImage("../../data/textures/map.png");
    LoadTextureImage("../../data/textures/red.png");
    LoadTextureImage("../../data/textures/monkey.png");
    LoadTextureImage("../../data/textures/metal.jpg");

    // create object models
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

    // start timer
    float current_time = (float)glfwGetTime();
    float previous_time_camera = current_time;
    float previous_time_bloon = current_time;
    float previous_time_dart = current_time;

    float delta_time_camera;
    float delta_time_bloon;
    float delta_time_dart;

    // aux var
    int b_idx, m_idx;

    // reset camera
    camera.reset(g_CameraTheta, g_CameraPhi, g_CameraDistance);

    // setup first level
    setupRound(1);

    // render window
    while(!glfwWindowShouldClose(window)){
        // define background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // paint framebuffer pixels and reset Z-buffer pixels
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // select GPU program
        glUseProgram(g_GpuProgramID);

        // update camera
        camera.update(g_CameraTheta, g_CameraPhi, g_CameraDistance);

        // update time
        current_time = (float)glfwGetTime();
        delta_time_camera = current_time - previous_time_camera;
        previous_time_camera = current_time;

        // check camera control keys
        if(W_pressed)
            camera.move('F', delta_time_camera, monkeys); // front

        if(A_pressed)
            camera.move('L', delta_time_camera, monkeys); // left

        if(S_pressed)
            camera.move('B', delta_time_camera, monkeys); // back

        if(D_pressed)
            camera.move('R', delta_time_camera, monkeys); // right

        if(SPACE_pressed)
            camera.move('U', delta_time_camera, monkeys); // up

        if(SHIFT_pressed)
            camera.move('D', delta_time_camera, monkeys); // down

        if(B_pressed){
            bloons[0].resetTime();
        }

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

        // draw plane
        model = Matrix_Scale(10.0f, 1.0f, 6.44f);

        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, PLANE);
        glUniform1i(g_shading_uniform, PHONG);

        DrawVirtualObject("plane");

        // get delta_time
        delta_time_bloon = current_time - previous_time_bloon;
        previous_time_bloon = current_time;

        updateBloons(delta_time_bloon);

        // draw bloons
        for(int i=0; i<int(bloons.size()); i++){
            if(bloons[i].isBlown() || !bloons[i].isReady())
                continue;
                
            glm::vec3 translation = bloons[i].getTranslation();
            model = Matrix_Translate(translation.x, translation.y, translation.z);

            glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
            glUniform1i(g_object_id_uniform, bloons[i].getModelId());
            glUniform1i(g_shading_uniform, PHONG);

            DrawVirtualObject(bloons[i].getModelName());
        }

        // iter for monkeys
        for(int i=0; i<int(monkeys.size()); i++){
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
        }

        // get delta_time
        delta_time_dart = current_time - previous_time_dart;
        previous_time_dart = current_time;

        // iter for darts
        for(int i = 0; i < int(darts.size()); i++){            
            if(darts[i].isAlive()){

                glm::vec4 translation = darts[i].getPosition();

                darts[i].setRotation();
                float rotation = darts[i].getRotation();

                model = Matrix_Translate(translation.x, translation.y, translation.z)
                    * Matrix_Rotate_Y(rotation);

                glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
                glUniform1i(g_object_id_uniform, 2);
                glUniform1i(g_shading_uniform, PHONG);

                DrawVirtualObject("dart");

                darts[i].updateDeltaPos(delta_time_dart);

                m_idx = darts[i].getMonkeyId();
                b_idx = darts[i].getBloonTargetId();

                glm::vec4 vec_t = bloons[b_idx].getTranslation();
                glm::mat4 mat_t = Matrix_Identity() * Matrix_Translate(vec_t.x, vec_t.y, vec_t.z);

                glm::vec4 bbox_t_max = mat_t * bloons[b_idx].getMaxBbox();
                glm::vec4 bbox_t_min = mat_t * bloons[b_idx].getMinBbox();

                if(is_ray_hit_bbox(bbox_t_min, bbox_t_max, darts[i].getPosition(), darts[i].getDeltaPos())){
                    bloons[b_idx].blow();
                    darts[i].setNotAlive();
                    monkeys[m_idx].setReady();

                }else{ 

                    darts[i].updatePosition();

                    if(!is_point_in_range(darts[i].getPosition(), darts[i].getInitialPosition(), darts[i].getRange())){
                        darts[i].setNotAlive();
                        monkeys[m_idx].setReady();
                    }
                }
            }
        }

        if((!previousRightMouseButtonPressed && g_RightMouseButtonPressed) && player.inStrategyMode() && player.canBuy(50)){

            float translation_x = ((g_LastCursorPosX / (SCREEN_WIDTH/2)) - 1) * 10.0;
            float translation_z = ((g_LastCursorPosY / (SCREEN_HEIGHT/2)) - 1) * 6.44;

            // printf("%f %f\n", translation_x, translation_z);

            if(monkeyPositionValid(translation_x, translation_z)){
                if(placeMonkey(translation_x, translation_z))
                    player.discountMoney(50);
            }
        }

        for(int i=0; i<int(bloons.size()); i++){
            if(bloons[i].reachedEnd()){
                player.discountLife(1);
                bloons[i].blow();
            }
        }

        if(player.lost()){
            break;
        }

        // update right mouse button control
        previousRightMouseButtonPressed = g_RightMouseButtonPressed;

        // print projection matrix
        TextRendering_ShowProjection(window);

        // print fps
        TextRendering_ShowFramesPerSecond(window);

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
