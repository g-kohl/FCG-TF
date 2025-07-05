#pragma once

// C++ headers
#include <vector>

// OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "camera.hpp"
#include "monkey.hpp"
#include "bloon.hpp"
#include "player.hpp"
#include "dart.hpp"

// Constants
#define SCREEN_WIDTH 826
#define SCREEN_HEIGHT 532

#define PLANE 0
#define BLOON 1
#define DART 2
#define MONKEY_LEVEL_1 3
#define MONKEY_LEVEL_2 4

#define PHONG 0
#define GOURAUD 1

// GPU Program
extern GLuint g_GpuProgramID;
extern GLint g_model_uniform;
extern GLint g_view_uniform;
extern GLint g_projection_uniform;
extern GLint g_object_id_uniform;
extern GLint g_shading_uniform;
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

// bloons
extern std::vector<Bloon> bloons;

// player
extern Player player;

// player's monkeys
extern std::vector<Monkey> monkeys;

// list of darts
extern std::vector<Dart> darts;

// create camera
extern Camera camera;

// spherical camera coordinates
extern float g_CameraTheta;
extern float g_CameraPhi;
extern float g_CameraDistance;

// cursor position
extern double g_LastCursorPosX, g_LastCursorPosY;

// mouse button flags
extern bool g_LeftMouseButtonPressed;
extern bool g_RightMouseButtonPressed;
extern bool g_MiddleMouseButtonPressed;

// loaded textures numbers
extern GLuint g_NumLoadedTextures;
