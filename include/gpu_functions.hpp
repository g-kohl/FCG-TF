#pragma once

// C++ headers
#include <string>
#include <fstream>
#include <sstream>

// OpenGL headers
// #include <glad/glad.h>

// Load object headers
#include <stb_image.h>

// Local headers
#include "globals.hpp"

void LoadShadersFromFiles(); // load shaders from file
void LoadTextureImage(const char* filename); // load texture
GLuint LoadShader_Vertex(const char* filename);   // load vertex shader
GLuint LoadShader_Fragment(const char* filename); // load fragment shader
void LoadShader(const char* filename, GLuint shader_id); // load shader
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id); // create GPU program