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
#include "collisions.hpp"
#include "scene_object.hpp"

// Constants
#define MONKEY_LEVEL_1_MODEL_ID 3
#define MONKEY_LEVEL_2_MODEL_ID 4

class Monkey{
    public:
        Monkey(glm::vec4 translation, float rotation, std::string modelName, int modelId);

        // translation
        glm::vec4 getTranslation();

        // bounding box
        glm::vec4 getMaxBbox();
        glm::vec4 getMinBbox();
        void setBbox();

        // rotation
        float getRotation();
        void lookToBloon(glm::vec4 position);

        // range
        float getRange();

        // cooldown
        float getCooldown();
        void updateCooldown(float deltaTime);
        void resetCooldown();

        // model name
        std::string getModelName();

        // model id
        int getModelId();

        // level
        int getLevel();
        void upgrade();

        // ready
        bool isReady();
        void setReady();
        void setNotReady();

    private:
        glm::vec4 translation;
        glm::vec4 bbox_max, bbox_min;
        float rotation, range, cooldown;
        std::string modelName;
        int modelId, level;
        bool ready;
};

int placeMonkey(float t_x, float t_z);
bool monkeyPositionValid(float t_x, float t_z);
void updateMonkeys(float deltaTime);