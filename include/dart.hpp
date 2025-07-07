#pragma once

// C++ headers
#include <string>
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"

// Constants
#define DART_MODEL_ID 2
#define VELOCITY 5.0f

class Dart{
    public:
        Dart(glm::vec4 initialPosition, glm::vec4 bloonTargetPosition, std::string modelName, int modelId, int bloonTargetId, int monkeyId, float range);

        // initial position
        glm::vec4 getInitialPosition();

        // position
        glm::vec4 getPosition();
        void updatePosition();

        // delta position
        glm::vec4 getDeltaPosition();
        void updateDeltaPosition(float deltaTime);

        // model name
        std::string getModelName();

        // model id
        int getModelId();

        // bloon target id
        int getBloonTargetId();

        // monkey id
        int getMonkeyId();

        // range
        float getRange();

        // rotation
        float getRotation();
        void setRotation();

        // alive
        bool isAlive();
        void setNotAlive();

    private:
        glm::vec4 initialPosition, position, velocity, deltaPosition, bloonTargetPosition;
        std::string modelName;
        int modelId, bloonTargetId, monkeyId;
        float range, rotation;
        bool alive;
};

void createDart(glm::vec4 monkeyPosition, glm::vec4 bloonPosition, int bloonId, int monkeyId, float range);