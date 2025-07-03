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
        Bloon(glm::vec3 translation, std::string modelName, int modelId);

        bool reachedEnd();

        glm::vec3 getTranslation();
        void setTranslation(glm::vec4 deltaPosition);

        std::string getModelName();

        int getLevel();

        int getModelId();

        float getTime();
        void resetTime();
        void updateTime(float deltaTime);

        bool isBlown();
        void blow();

    private:
        glm::vec3 translation;
        std::string modelName;
        int modelId, level;
        float time;
        bool blown;
};

void setupLevel(int level);

void updateBloons(float deltaTime);