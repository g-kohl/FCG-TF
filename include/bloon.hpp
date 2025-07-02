#pragma once

// C++ headers
#include <vector>

// GLM headers
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Local Headers
#include "player.hpp"
#include "animation_functions.hpp"

class Bloon{
    public:
        glm::vec3 translation, scaling, rotation;
        const char* object_model_name;
        int object_model_id, level;
        float time;

        Bloon(float t_x,float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, float r_y, float r_z, const char* name, int id);
        bool reachedEnd();

    private:
};

void setupLevel(int level);

void updateBloons(float deltaTime);