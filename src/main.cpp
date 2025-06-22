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
#include "animation_functions.hpp"
#include "monkey.hpp"
#include "bloon.hpp"

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
    window = glfwCreateWindow(800, 600, "Bloons 3D", NULL, NULL);

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
    FramebufferSizeCallback(window, 800, 600);

    // print GPU informations
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    // load shaders
    LoadShadersFromFiles();

    // load textures
    LoadTextureImage("../../data/map.png");
    LoadTextureImage("../../data/red.png");
    LoadTextureImage("../../data/brown.png");

    // create object models
    ObjectModel bloonModel("../../data/bloon.obj");
    bloonModel.ComputeNormals();
    bloonModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel planeModel("../../data/plane.obj");
    planeModel.ComputeNormals();
    planeModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel monkeyLevel1Model("../../data/monkey_level_1.obj");
    monkeyLevel1Model.ComputeNormals();
    monkeyLevel1Model.BuildTrianglesAndAddToVirtualScene();

    ObjectModel monkeyLevel2Model("../../data/monkey_level_2.obj");
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

    // start timer
    float current_time = (float)glfwGetTime();
    float previous_time_camera = current_time;
    float previous_time_bloon = current_time;
    float delta_time_camera;
    float delta_time_bloon;
    float t_time;

    std::vector<glm::vec4> points = {
        glm::vec4(-8.0f, 0.0f, -1.6f, 1.0f),
        glm::vec4(-4.15f, 0.0f, -1.6f, 1.0f),
        glm::vec4(-0.3f, 0.0f, -1.6f, 1.0f),

        glm::vec4(3.0f, 0.0f, -7.0f, 1.0f),
        glm::vec4(-3.5f, 0.0f, -5.0f, 1.0f),

        glm::vec4(-3.5f, 0.0f, 0.5f, 1.0f),
        glm::vec4(-3.5f, 0.0f, 6.0f, 1.0f),

        glm::vec4(-8.0f, 0.0f, 4.5f, 1.0f),
        glm::vec4(-5.0f, 0.0f, 1.5f, 1.0f),

        glm::vec4(-1.25f, 0.0f, 1.5f, 1.0f),
        glm::vec4(2.5f, 0.0f, 1.5f, 1.0f),

        glm::vec4(2.0f, 0.0f, -5.0f, 1.0f),
        glm::vec4(5.0f, 0.0f, -3.0f, 1.0f),

        glm::vec4(5.0f, 0.0f, 0.75f, 1.0f),
        glm::vec4(5.0f, 0.0f, 4.5f, 1.0f),

        glm::vec4(-2.0f, 0.0f, 3.0f, 1.0f),
        glm::vec4(-1.3f, 0.0f, 9.0f, 1.0f),
    };

    // Initial bloon position 
    glm::vec4 bloon_position = glm::vec4(-8.0f, 0.0f, -2.0f, 0.1f);

    bool tem_macaco = false;
    Monkey monkey = Monkey(
        9.0f, -1.1f, 6.0f,
        0.008f, 0.008f, 0.008f,
        0.0f, M_PI, 0.0f,
        "monkey_level_1", 2);

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
            camera.move('F', delta_time_camera); // front

        if(A_pressed)
            camera.move('L', delta_time_camera); // left

        if(S_pressed)
            camera.move('B', delta_time_camera); // back

        if(D_pressed)
            camera.move('R', delta_time_camera); // right

        if(SPACE_pressed)
            camera.move('U', delta_time_camera); // up

        if(SHIFT_pressed)
            camera.move('D', delta_time_camera); // down

        if(B_pressed)
            t_time = 0;

        // compute view matrix
        glm::mat4 view = Matrix_Camera_View(camera.position, camera.view_vector, camera.up_vector);

        // compute projection matrix
        glm::mat4 projection;

        float nearplane = -0.1f;
        float farplane  = -50.0f;

        if(g_UsePerspectiveProjection){
            // perspective projection
            float field_of_view = 3.141592 / 3.0f;
            projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
        }
        else
        {
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

        // draw objects
        #define PLANE 0
        #define BLOON 1
        #define MONKEY_LEVEL_1 2
        #define MONKEY_LEVEL_2 3

        // draw plane
        model = Matrix_Translate(0.0f,-1.1f,0.0f)
              * Matrix_Scale(10.0f,1.0f,6.44f);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, PLANE);
        DrawVirtualObject("plane");

        // get delta_time
        delta_time_bloon = current_time - previous_time_bloon;
        previous_time_bloon = current_time;
        t_time += delta_time_bloon;

        glm::vec4 d = bezier_spline(points, t_time);

        // update bloon position
        glm::vec4 v_vec = d - bloon_position;
        bloon_position = bloon_position + v_vec; 

        // draw bloons
        Bloon bloon = Bloon(
            bloon_position.x, 0.0f, bloon_position.z,
            0.3f, 0.3f, 0.3f,
            0.0f, 0.0f, 0.0f,
            "bloon", BLOON);

        model = Matrix_Translate(bloon.translation.x, bloon.translation.y, bloon.translation.z)
              * Matrix_Scale(bloon.scaling.x, bloon.scaling.y, bloon.scaling.z)
              * Matrix_Rotate_X(bloon.rotation.x) * Matrix_Rotate_Y(bloon.rotation.y) * Matrix_Rotate_Z(bloon.rotation.z);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, bloon.object_model_id);
        DrawVirtualObject(bloon.object_model_name);

        // draw monkeys
        if(g_RightMouseButtonPressed){
            tem_macaco = true;

            printf("\n%f %f", g_LastCursorPosX, g_LastCursorPosY);

            // tela: x = [0, 800], y = [0, 600]
            // mapa: x = [-9, 9], y = [-6, 6]

            monkey.translation.x = ((g_LastCursorPosX / 400) - 1) * 9;
            monkey.translation.z = ((g_LastCursorPosY / 300) - 1) * 6;
        }

        if(tem_macaco){
            model = Matrix_Translate(monkey.translation.x, monkey.translation.y, monkey.translation.z)
                * Matrix_Scale(monkey.scaling.x, monkey.scaling.y, monkey.scaling.z)
                * Matrix_Rotate_X(monkey.rotation.x) * Matrix_Rotate_Y(monkey.rotation.y) * Matrix_Rotate_Z(monkey.rotation.z);
            glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
            glUniform1i(g_object_id_uniform, monkey.object_model_id);
            DrawVirtualObject(monkey.object_model_name);
        }

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
