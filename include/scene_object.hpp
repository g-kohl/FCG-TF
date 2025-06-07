#pragma once

// C++ headers
#include <map>
#include <string>

// OpenGL headers
#include <glad/glad.h>

// GLM headers
#include <glm/mat4x4.hpp>

struct SceneObject
{
    std::string name;
    size_t first_index;
    size_t num_indices;
    GLenum rendering_mode;
    GLuint vertex_array_object_id;
    glm::vec3 bbox_min;
    glm::vec3 bbox_max;
};

extern std::map<std::string, SceneObject> g_VirtualScene;