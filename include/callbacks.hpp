#pragma once

// C headers
#include <cstdlib>
#include <cstdio>

// OpenGL headers
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// Local headers
#include "globals.hpp"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);