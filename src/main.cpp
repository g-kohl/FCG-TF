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

    // create object models
    ObjectModel balloonModel("../../data/balloon.obj");
    balloonModel.ComputeNormals();
    balloonModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel planemodel("../../data/plane.obj");
    planemodel.ComputeNormals();
    planemodel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel monkeyModel("../../data/monkey.obj");
    monkeyModel.ComputeNormals();
    monkeyModel.BuildTrianglesAndAddToVirtualScene();

    ObjectModel bigMonkeyModel("../../data/big_monkey.obj");
    bigMonkeyModel.ComputeNormals();
    bigMonkeyModel.BuildTrianglesAndAddToVirtualScene();

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
    float previous_time = (float)glfwGetTime();
    float current_time;
    float delta_time;

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
        delta_time = current_time - previous_time;
        previous_time = current_time;

        // check camera control keys
        if(W_pressed)
            camera.move('W', delta_time);

        if(A_pressed)
            camera.move('A', delta_time);

        if(S_pressed)
            camera.move('S', delta_time);

        if(D_pressed)
            camera.move('D', delta_time);

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
        #define BALLOON 0
        #define PLANE  1
        #define MONKEY 2
        #define BIGMONKEY 3

        model = Matrix_Translate(-8.0f,0.0f,-1.5f)
              * Matrix_Scale(0.5f, 0.5f, 0.5f);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, BALLOON);
        DrawVirtualObject("balloon");

        model = Matrix_Translate(0.0f,-1.1f,0.0f)
              * Matrix_Scale(10.0f,10.0f,10.0f);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, PLANE);
        DrawVirtualObject("the_plane");

        model = Matrix_Translate(-5.0f,-1.0f,0.0f)
              * Matrix_Scale(0.01f,0.01f,0.01f)
              * Matrix_Rotate_Y(M_PI);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, MONKEY);
        DrawVirtualObject("monkey");

        model = Matrix_Translate(-1.0f,-1.5f,-3.0f)
              * Matrix_Scale(0.05f,0.05f,0.05f);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, BIGMONKEY);
        DrawVirtualObject("big_monkey");

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
