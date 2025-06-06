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
    std::string name; // object name
    size_t first_index; // first vertex index
    size_t num_indices; // indexes number
    GLenum rendering_mode; // rendering mode
    GLuint vertex_array_object_id; // VAO ID
    glm::vec3 bbox_min; // AABB
    glm::vec3 bbox_max;
};

// virtual scene
extern std::map<std::string, SceneObject> g_VirtualScene;