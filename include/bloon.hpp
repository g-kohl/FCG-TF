#pragma once

// C++ headers
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local Headers
#include "player.hpp"
#include "animation_functions.hpp"
#include "scene_object.hpp"

// Constants
#define MAX_LEVEL 1

class Bloon{
    public:
        Bloon(glm::vec4 translation, std::string modelName, int modelId, int level, float time);

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

        bool isReady();
        void setReady();

        bool isBlown();
        void blow();

    private:
        glm::vec4 translation;
        glm::vec4 bbox_max, bbox_min;
        std::string modelName;
        int modelId, level;
        float time;
        bool ready, blown;
};

void setupRound(int level);

void updateBloons(float deltaTime);