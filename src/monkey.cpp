#include "monkey.hpp"

std::vector<Monkey> monkeys;

Monkey::Monkey(glm::vec3 translation, glm::vec3 rotation, std::string modelName, int modelId)
    : translation(translation), rotation(rotation), modelName(modelName), modelId(modelId), level(1), targetId(-1) {}


glm::vec3 Monkey::getTranslation(){
    return translation;
}
    
glm::vec3 Monkey::getRotation(){
    return rotation;
}

std::string Monkey::getModelName(){
    return modelName;
}

int Monkey::getLevel(){
    return level;
}

void Monkey::upgrade(){
    modelName = "monkey_level_2";
    modelId = 2;
    level = 2;
}

int Monkey::getModelId(){
    return modelId;
}

void placeMonkey(float t_x, float t_z){
    glm::vec3 translationVector = glm::vec3(t_x, 0.0f, t_z);
    glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 0.0f);

    Monkey monkey = Monkey(translationVector, rotationVector, "monkey_level_1", 2);

    monkeys.push_back(monkey);
}