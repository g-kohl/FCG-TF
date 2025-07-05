#pragma once

// C++ headers
#include <string>
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"

class Dart{
    public:
        Dart(glm::vec4 initialPosition, int bloonTargetId, int monkeyId, glm::vec4 bloonTargetPos, float range);

        glm::vec4 getPosition();
        glm::vec4 getInitialPosition();
        glm::vec4 getDeltaPos();

        float getRange();
        int getBloonTargetId();
        int getMonkeyId();
        std::string getModelName();

        void updatePosition();
        void updateDeltaPos(float deltaTime);

        float getRotation();
        void setRotation();

        bool isAlive();
        void setNotAlive();

    private:
        glm::vec4 initialPosition, position, velocity, deltaPos, bloonTargetPos;
        std::string modelName = "dart";
        int bloonTargetId, monkeyId;
        float range, rotation;
        bool alive;
};

void createDart(glm::vec4 monkeyPos, int b_id, int m_id, glm::vec4 bloonPos, float range);