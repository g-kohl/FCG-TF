#include "dart.hpp"

std::vector<Dart> darts;

Dart::Dart(glm::vec4 initialPosition, int bloonTargetId, int monkeyId, glm::vec4 bloonTargetPos, float range)
    : initialPosition(initialPosition), position(initialPosition), bloonTargetPos(bloonTargetPos), bloonTargetId(bloonTargetId), monkeyId(monkeyId), range(range), alive(true) {

        glm::vec4 v_dir = bloonTargetPos - initialPosition;
        velocity = v_dir * 2.0f;
    }

glm::vec4 Dart::getPosition(){
    return position;
}

float Dart::getRange(){
    return range;
}

void Dart::updatePosition(){
    position = position + deltaPos;
}

void Dart::updateDeltaPos(float deltaTime){
    deltaPos = velocity * deltaTime;
}

bool Dart::isAlive(){
    return alive;
}

glm::vec4 Dart::getInitialPosition(){
    return initialPosition;
}

int Dart::getBloonTargetId(){
    return bloonTargetId;
}

glm::vec4 Dart::getDeltaPos(){
    return deltaPos;
}

void Dart::setNotAlive(){
    alive = false;
} 

int Dart::getMonkeyId(){
    return monkeyId;
}

float Dart::getRotation(){
    return rotation;
}

void Dart::setRotation(){
    glm::vec4 direction = bloonTargetPos - initialPosition;
    direction.y = 0.0f;
    direction /= norm(direction);

    if(norm(direction) < 0.0001f){
        rotation = 0.0f;
        return;
    }

    rotation = atan2(direction.x, direction.z) + 3.141592;
}

void createDart(glm::vec4 monkeyPos, int b_id, int m_id, glm::vec4 bloonPos, float range){
    Dart new_dart = Dart(monkeyPos, b_id, m_id, bloonPos, range);
    darts.push_back(new_dart);
}