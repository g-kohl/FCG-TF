#pragma once

// C++ headers
#include <string>
#include <fstream>
#include <sstream>

// Load object headers
#include <stb_image.h>

// Local headers
#include "globals.hpp"

void LoadShadersFromFiles();
void LoadTextureImage(const char* filename);
GLuint LoadShader_Vertex(const char* filename);
GLuint LoadShader_Fragment(const char* filename);
void LoadShader(const char* filename, GLuint shader_id);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
