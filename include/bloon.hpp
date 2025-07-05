#pragma once

// C++ headers
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local Headers
#include "player.hpp"
#include "animation_functions.hpp"

#include "scene_object.hpp"

class Bloon{
    public:
        Bloon(glm::vec4 translation, std::string modelName, int modelId);

        bool reachedEnd();

        glm::vec4 getTranslation();
        void setTranslation(glm::vec4 deltaPosition);

        std::string getModelName();

        int getLevel();

        glm::vec4 getMaxBbox();
        glm::vec4 getMinBbox();

        int getModelId();

        float getTime();
        void resetTime();
        void updateTime(float deltaTime);

        bool isBlown();
        void blow();

    private:
        glm::vec4 translation;
        glm::vec4 bbox_max, bbox_min;
        std::string modelName;
        int modelId, level;
        float time;
        bool blown;
};

void setupLevel(int level);

void updateBloons(float deltaTime);