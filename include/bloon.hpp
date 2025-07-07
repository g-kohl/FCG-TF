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
#define MAX_MAP_HEIGHT 6.0
#define INITIAL_POSITION glm::vec4(-8.0f, 1.0f, -2.0f, 0.0f)
#define MAX_LEVEL 4
#define BLOON_MODEL_ID 1

class Bloon{
    public:
        Bloon(glm::vec4 translation, std::string modelName, int modelId, int level, float time);

        // translation
        glm::vec4 getTranslation();
        bool reachedEnd();
        void setTranslation(glm::vec4 deltaPosition);
        void updateTranslation(float deltaTime);

        // bounding box
        glm::vec4 getMaxBbox();
        glm::vec4 getMinBbox();

        // model name
        std::string getModelName();

        // model id
        int getModelId();

        // level
        int getLevel();
        void loseLevel(int damage);

        // time
        float getTime();
        void updateTime(float deltaTime);
        void resetTime();

        // ready
        bool isReady();
        void setReady();

        // blown
        bool isBlown();
        void blow();

    private:
        glm::vec4 translation, bbox_max, bbox_min;
        std::string modelName;
        int modelId, level;
        float time;
        bool ready, blown;
};

void setupRound(int level);
bool roundFinished();