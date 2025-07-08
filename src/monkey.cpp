#include "monkey.hpp"

// list of monkeys
std::vector<Monkey> monkeys;

// constructor
Monkey::Monkey(glm::vec4 translation, float rotation, std::string modelName, int modelId)
    : translation(translation), rotation(rotation), range(3.0f), cooldown(3.0f), modelName(modelName), modelId(modelId), level(1), ready(true) {
        setBbox();
    }

// translation

glm::vec4 Monkey::getTranslation(){
    return translation;
}

// bounding box

glm::vec4 Monkey::getMaxBbox(){
    return bbox_max;
}

glm::vec4 Monkey::getMinBbox(){
    return bbox_min;
}

void Monkey::setBbox(){
    SceneObject object = g_VirtualScene[modelName];
    bbox_max = glm::vec4(object.bbox_max.x, object.bbox_max.y, object.bbox_max.z, 1.0f);
    bbox_min = glm::vec4(object.bbox_min.x, object.bbox_min.y, object.bbox_min.z, 1.0f);

    glm::mat4 mat_t = Matrix_Identity() * Matrix_Translate(translation.x, translation.y, translation.z);

    bbox_max = mat_t * bbox_max;
    bbox_min = mat_t * bbox_min;
}

// rotation
    
float Monkey::getRotation(){
    return rotation;
}

////////////////////////// FONTE: Chat-GPT
void Monkey::lookToBloon(glm::vec4 position){ // chat GPT
    glm::vec4 lookDirection = position - translation;
    lookDirection.y = 0.0f;
    lookDirection /= norm(lookDirection);

    if(norm(lookDirection) < 0.0001f){
        rotation = 0.0f;
        return;
    }

    rotation = atan2(lookDirection.x, lookDirection.z) + 3.141592; 
}
//////////////////////////

// range

float Monkey::getRange(){
    return range;
}

// cooldown

float Monkey::getCooldown(){
    return cooldown;
}

void Monkey::updateCooldown(float deltaTime){
    cooldown += deltaTime;
}

void Monkey::resetCooldown(){
    cooldown = 0.0f;
}

// model name

std::string Monkey::getModelName(){
    return modelName;
}

// model id

int Monkey::getModelId(){
    return modelId;
}

// level

int Monkey::getLevel(){
    return level;
}

void Monkey::upgrade(){
    modelName = "monkey_level_2";
    modelId = MONKEY_LEVEL_2_MODEL_ID;
    level = 2;
}

// ready

bool Monkey::isReady(){
    return ready;
}

void Monkey::setReady(){
    ready = true;
}

void Monkey::setNotReady(){
    ready = false;
}

bool monkeyPositionValid(float t_x, float t_z){
    // check if the position is in the bloons' path
    if(t_x >= -10.5 && t_x <= 1.0 && t_z >= -2.0 && t_z <= -0.5)
        return false;

    if(t_x >= -1.0 && t_x <= 1.0 && t_z >= -5.0 && t_z <= 0.0)
        return false;

    if(t_x >= -4.5 && t_x <= 1.0 && t_z >= -5.0 && t_z <= -3.0)
        return false;

    if(t_x >= -4.5 && t_x <= -2.5 && t_z >= -5.0 && t_z <= 5.0)
        return false;

    if(t_x >= -8.0 && t_x <= -2.5 && t_z >= 3.0 && t_z <= 5.0)
        return false;

    if(t_x >= -8.0 && t_x <= -6.0 && t_z >= 0.0 && t_z <= 5.0)
        return false;

    if(t_x >= -8.0 && t_x <= 4.0 && t_z >= 0.5 && t_z <= 2.0)
        return false;

    if(t_x >= 1.5 && t_x <= 3.5 && t_z >= -3.0 && t_z <= 1.5)
        return false;

    if(t_x >= 2.0 && t_x <= 6.0 && t_z >= -3.0 && t_z <= -1.0)
        return false;

    if(t_x >= 4.5 && t_x <= 6.0 && t_z >= -3.0 && t_z <= 4.0)
        return false;

    if(t_x >= -2.0 && t_x <= 6.0 && t_z >= 2.5 && t_z <= 4.0)
        return false;

    if(t_x >= -2.0 && t_x <= 0.0 && t_z >= 2.0 && t_z <= 7.0)
        return false;

    return true;
}

int placeMonkey(float t_x, float t_z){
    glm::vec4 translationVector = glm::vec4(t_x, 0.0f, t_z, 0.0f);
    Monkey monkey = Monkey(translationVector, 0.0f, "monkey_level_1", MONKEY_LEVEL_1_MODEL_ID);

    for(int i = 0; i < int(monkeys.size()); i++){ 
        if(is_bbox_hit_bbox(monkeys[i].getMinBbox(), monkeys[i].getMaxBbox(), monkey.getMinBbox(), monkey.getMaxBbox()))
            return i;
    }

    monkeys.push_back(monkey);
    return -1;
}

void updateMonkeys(float deltaTime){

}