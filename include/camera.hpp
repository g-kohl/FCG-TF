#pragma once

// C/C++ headers
#include <cmath>
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"
#include "monkey.hpp"
#include "collisions.hpp"

class Camera{
    public:
        Camera(float theta, float phi, float distance);

        // free
        bool getMode();
        void setMode(bool mode);

        // position
        glm::vec4 getPosition();
        void move(char direction, float deltaTime, std::vector<Monkey> &monkeys);
        void update(float theta, float phi, float distance);
        void reset(float &theta, float &phi, float &distance);
        bool isReset(float &theta, float &phi, float &distance);

        // view vector
        glm::vec4 getViewVector();

        // up vector
        glm::vec4 getUpVector();
        
    private:
        bool free;
        float speed;
        glm::vec4 position, lookat, viewVector, upVector, wVector, uVector;

        void computeVectors();
        bool checkBboxCollisions(glm::vec4 nextPosition, std::vector<Monkey> &monkeys);
};