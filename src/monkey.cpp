#include "monkey.hpp"

std::vector<Monkey> monkeys;

Monkey::Monkey(glm::vec4 translation, float rotation, std::string modelName, int modelId)
    : translation(translation), rotation(rotation), range(5.0f), modelName(modelName), modelId(modelId), level(1), ready(true) {}


glm::vec4 Monkey::getTranslation(){
    return translation;
}
    
float Monkey::getRotation(){
    return rotation;
}

void Monkey::lookToBloon(glm::vec4 position){
    glm::vec4 lookDirection = position - translation;
    lookDirection.y = 0.0f;
    lookDirection /= norm(lookDirection);

    if(norm(lookDirection) < 0.0001f){
        rotation = 0.0f;
        return;
    }

    rotation = atan2(lookDirection.x, lookDirection.z) + 3.141592; 
}

std::string Monkey::getModelName(){
    return modelName;
}

int Monkey::getLevel(){
    return level;
}

float Monkey::getRange(){
    return range;
}

void Monkey::upgrade(){
    modelName = "monkey_level_2";
    modelId = 4;
    level = 2;
}

int Monkey::getModelId(){
    return modelId;
}

bool Monkey::isReady(){
    return ready;
}

void Monkey::setReady(){
    ready = true;
}

void Monkey::setNotReady(){
    ready = false;
}

void placeMonkey(float t_x, float t_z){
    glm::vec4 translationVector = glm::vec4(t_x, 0.0f, t_z, 0.0f);

    Monkey monkey = Monkey(translationVector, 0.0f, "monkey_level_1", 3);

    monkeys.push_back(monkey);
}