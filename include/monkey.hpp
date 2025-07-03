#pragma once

// C headers
#include <cmath>

// C++ headers
#include <string>
#include <vector>

// GLM headers
#include <glm/vec3.hpp>

class Monkey{
    public:
        Monkey(glm::vec3 translation, glm::vec3 rotation, std::string modelName, int modelId);

        glm::vec3 getTranslation();
        glm::vec3 getRotation();

        std::string getModelName();

        int getLevel();
        void upgrade();

        int getModelId();

    private:
        glm::vec3 translation, rotation;
        std::string modelName;
        int modelId, level, targetId;
};

void placeMonkey(float t_x, float t_z);