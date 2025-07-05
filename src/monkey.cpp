#include "monkey.hpp"

std::vector<Monkey> monkeys;

Monkey::Monkey(glm::vec4 translation, glm::vec4 rotation, std::string modelName, int modelId)
    : translation(translation), rotation(rotation), modelName(modelName), modelId(modelId), level(1), range(2.0f), ready(true) {}


glm::vec4 Monkey::getTranslation(){
    return translation;
}
    
glm::vec4 Monkey::getRotation(){
    return rotation;
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
    modelId = 2;
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
    glm::vec4 rotationVector = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    Monkey monkey = Monkey(translationVector, rotationVector, "monkey_level_1", 2);

    monkeys.push_back(monkey);
}