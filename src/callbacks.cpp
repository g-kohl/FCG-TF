#include "callbacks.hpp"

float g_ScreenRatio = 1.0f;

bool g_UsePerspectiveProjection = true;

bool g_ShowInfoText = true;

bool W_pressed = false;
bool A_pressed = false;
bool S_pressed = false;
bool D_pressed = false;
bool B_pressed = false;
bool SHIFT_pressed = false;
bool SPACE_pressed = false;

float g_CameraTheta = 0.0f;
float g_CameraPhi = 0.0f;
float g_CameraDistance = 3.5f;

Camera camera = Camera(g_CameraTheta, g_CameraPhi, g_CameraDistance);

double g_LastCursorPosX, g_LastCursorPosY;

bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false;
bool g_MiddleMouseButtonPressed = false;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

    g_ScreenRatio = (float)width / height;
}

void ErrorCallback(int error, const char* description){
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod){
    for(int i = 0; i < 10; ++i)
        if(key == GLFW_KEY_0 + i && action == GLFW_PRESS && mod == GLFW_MOD_SHIFT)
            std::exit(100 + i);

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(key == GLFW_KEY_P && action == GLFW_PRESS){
        g_UsePerspectiveProjection = true;
    }

    if(key == GLFW_KEY_O && action == GLFW_PRESS){
        g_UsePerspectiveProjection = false;
    }

    if(key == GLFW_KEY_H && action == GLFW_PRESS){
        g_ShowInfoText = !g_ShowInfoText;
    }

    if(key == GLFW_KEY_W){
        if(action == GLFW_PRESS){
            W_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            W_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_A){
        if(action == GLFW_PRESS){
            A_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            A_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_S){
        if(action == GLFW_PRESS){
            S_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            S_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_D){
        if(action == GLFW_PRESS){
            D_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            D_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_B){
        if(action == GLFW_PRESS){
            B_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            B_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_LEFT_SHIFT){
        if(action == GLFW_PRESS){
            SHIFT_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            SHIFT_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_SPACE){
        if(action == GLFW_PRESS){
            SPACE_pressed = true;

        }
        else if(action == GLFW_RELEASE){
            SPACE_pressed = false;

        }
        else if(action == GLFW_REPEAT);
    }

    if(key == GLFW_KEY_R && action == GLFW_PRESS){
        // LoadShadersFromFiles();
        // fprintf(stdout,"Shaders recarregados!\n");
        // fflush(stdout);
    }

    if(key == GLFW_KEY_F && action == GLFW_PRESS){
        camera.free = !camera.free;
    }

    if(key == GLFW_KEY_C && action == GLFW_PRESS){
        camera.reset(g_CameraTheta, g_CameraPhi, g_CameraDistance);
        canPlaceMonkey = true;
    }
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        g_LeftMouseButtonPressed = false;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_RightMouseButtonPressed = true;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
        g_RightMouseButtonPressed = false;
    }
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_MiddleMouseButtonPressed = true;
    }
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
        g_MiddleMouseButtonPressed = false;
    }
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    if(g_LeftMouseButtonPressed){
        float dx = xpos - g_LastCursorPosX;
        float dy = ypos - g_LastCursorPosY;

        g_CameraTheta -= 0.01f*dx;
        g_CameraPhi   += 0.01f*dy;

        float phimax = 3.141592f/2;
        float phimin = -phimax;
    
        if (g_CameraPhi > phimax)
            g_CameraPhi = phimax;
    
        if (g_CameraPhi < phimin)
            g_CameraPhi = phimin;

        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if(g_RightMouseButtonPressed){
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if(g_MiddleMouseButtonPressed){    
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    g_CameraDistance -= 0.1f*yoffset;

    const float verysmallnumber = std::numeric_limits<float>::epsilon();

    if(g_CameraDistance < verysmallnumber)
        g_CameraDistance = verysmallnumber;
}
