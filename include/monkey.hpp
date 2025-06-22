#pragma once

// GLM headers
#include <glm/vec3.hpp>

class Monkey{
    public:
        glm::vec3 translation, scaling, rotation;
        const char* object_model_name;
        int object_model_id, level;

        Monkey(float t_x,float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, float r_y, float r_z, const char* name, int id);

    private:
};