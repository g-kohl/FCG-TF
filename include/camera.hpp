#pragma once

#include "matrices.h"
#include <cmath>
#include <glm/vec4.hpp>


class Camera {
    public:
        bool free;
        float theta, phi, distance;
        float x, y, z;
        float speed;
        glm::vec4 position, lookat, view_vector, up_vector, w_vector, u_vector;

        Camera(float theta, float phi, float distance);
        void changeMode();
        void move(char direction, float delta_time);
        void update(float theta, float phi, float distance);
    private:

};