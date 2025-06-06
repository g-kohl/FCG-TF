#pragma once

// C headers
#include <cmath>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"


class Camera{
    public:
        bool free;
        float speed;
        glm::vec4 position, lookat, view_vector, up_vector, w_vector, u_vector;

        Camera(float theta, float phi, float distance);
        void move(char direction, float delta_time);
        void update(float theta, float phi, float distance);
        void reset(float &theta, float &phi, float &distance);
        
    private:

};