#pragma once

// C headers
#include <cmath>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"


class Camera{
    public:
        Camera(float theta, float phi, float distance);

        bool getMode();
        void setMode(bool mode);

        glm::vec4 getPosition();
        glm::vec4 getViewVector();
        glm::vec4 getUpVector();

        void move(char direction, float deltaTime);
        void update(float theta, float phi, float distance);
        void reset(float &theta, float &phi, float &distance);
        
    private:
        bool free;
        float speed;
        glm::vec4 position, lookat, viewVector, upVector, wVector, uVector;

        void computeVectors();
};