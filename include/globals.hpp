#pragma once

// OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "camera.hpp"

// GPU Program
extern GLuint g_GpuProgramID;
extern GLint g_model_uniform;
extern GLint g_view_uniform;
extern GLint g_projection_uniform;
extern GLint g_object_id_uniform;
extern GLint g_bbox_min_uniform;
extern GLint g_bbox_max_uniform;

// screen ratio
extern float g_ScreenRatio;

// projection flag
extern bool g_UsePerspectiveProjection;

// print flag
extern bool g_ShowInfoText;

// camera control keys flags
extern bool W_pressed;
extern bool A_pressed;
extern bool S_pressed;
extern bool D_pressed;
extern bool SHIFT_pressed;
extern bool SPACE_pressed;

// reset balloon flag
extern bool B_pressed;

// create camera
extern Camera camera;

// spherical camera coordinates
extern float g_CameraTheta;
extern float g_CameraPhi;
extern float g_CameraDistance;

extern double g_LastCursorPosX, g_LastCursorPosY;

// mouse button flags
extern bool g_LeftMouseButtonPressed;
extern bool g_RightMouseButtonPressed;
extern bool g_MiddleMouseButtonPressed;

// loaded textures numbers
extern GLuint g_NumLoadedTextures;
