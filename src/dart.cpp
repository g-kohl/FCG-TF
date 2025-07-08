#include "dart.hpp"

// list of darts
std::vector<Dart> darts;

// constructor
Dart::Dart(glm::vec4 initialPosition, glm::vec4 bloonTargetPosition, std::string modelName, int modelId, int bloonTargetId, int monkeyId, float range)
    : initialPosition(initialPosition), position(initialPosition), bloonTargetPosition(bloonTargetPosition), modelName(modelName), modelId(modelId), bloonTargetId(bloonTargetId), monkeyId(monkeyId), range(range), alive(true) {

        glm::vec4 velocity_direction = bloonTargetPosition - initialPosition;
        velocity = velocity_direction * VELOCITY;
    }

// initial position

glm::vec4 Dart::getInitialPosition(){
    return initialPosition;
}

// position

glm::vec4 Dart::getPosition(){
    return position;
}

void Dart::updatePosition(){
    position = position + deltaPosition;
}

// delta position

glm::vec4 Dart::getDeltaPosition(){
    return deltaPosition;
}

void Dart::updateDeltaPosition(float deltaTime){
    deltaPosition = velocity * deltaTime;
}

// model name

std::string Dart::getModelName(){
    return modelName;
}

// model id

int Dart::getModelId(){
    return modelId;
}

// bloon target id

int Dart::getBloonTargetId(){
    return bloonTargetId;
}

// monkey id

int Dart::getMonkeyId(){
    return monkeyId;
}

// range

float Dart::getRange(){
    return range;
}

// rotation

float Dart::getRotation(){
    return rotation;
}

////////////////////////// FONTE: Chat-GPT
void Dart::setRotation(){
    glm::vec4 direction = bloonTargetPosition - initialPosition;
    direction.y = 0.0f;
    direction /= norm(direction);

    if(norm(direction) < 0.0001f){
        rotation = 0.0f;
        return;
    }

    rotation = atan2(direction.x, direction.z) + 3.141592;
}
//////////////////////////

// alive

bool Dart::isAlive(){
    return alive;
}

void Dart::setNotAlive(){
    alive = false;
} 

void createDart(glm::vec4 monkeyPosition, glm::vec4 bloonPosition, int bloonId, int monkeyId, float range){
    Dart new_dart = Dart(monkeyPosition, bloonPosition, "dart", DART_MODEL_ID, bloonId, monkeyId, range);
    darts.push_back(new_dart);
}