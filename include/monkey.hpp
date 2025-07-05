#pragma once

// C headers
#include <cmath>

// C++ headers
#include <string>
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

class Monkey{
    public:
        Monkey(glm::vec4 translation, glm::vec4 rotation, std::string modelName, int modelId);

        glm::vec4 getTranslation();
        glm::vec4 getRotation();

        std::string getModelName();

        int getLevel();
        float getRange();
        void upgrade();

        int getModelId();

        bool isReady();
        void setNotReady();
        void setReady();

    private:
        glm::vec4 translation, rotation;
        std::string modelName;
        int modelId, level;
        float range;
        bool ready; // if the monkey is able to shoot
};

void placeMonkey(float t_x, float t_z);