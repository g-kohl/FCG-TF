#pragma once

// C headers
#include <cmath>

// C++ headers
#include <string>
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"

class Monkey{
    public:
        Monkey(glm::vec4 translation, float rotation, std::string modelName, int modelId);

        glm::vec4 getTranslation();

        float getRotation();
        void lookToBloon(glm::vec4 position);

        std::string getModelName();

        int getLevel();
        float getRange();
        void upgrade();

        int getModelId();

        bool isReady();
        void setNotReady();
        void setReady();

    private:
        glm::vec4 translation;
        float rotation, range;
        std::string modelName;
        int modelId, level;
        bool ready; // if the monkey is able to shoot
};

bool monkeyPositionValid(float t_x, float t_z);
void placeMonkey(float t_x, float t_z);