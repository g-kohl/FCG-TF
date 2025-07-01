#include "monkey.hpp"

std::vector<Monkey> monkeys;

Monkey::Monkey(float t_x,float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, float r_y, float r_z, std::string name, int id){
    translation = glm::vec3(t_x, t_y, t_z);
    scaling = glm::vec3(s_x, s_y, s_z);
    rotation = glm::vec3(r_x, r_y, r_z);

    object_model_name = name;
    object_model_id = id;
    level = 1;
}

void Monkey::upgradeMonkey(){
    object_model_name = "monkey_level_2";
    object_model_id = 2;
    level = 2;
}

void placeMonkey(float t_x, float t_z){
    Monkey monkey = Monkey(
        t_x, 0.0f, t_z,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        "monkey_level_1", 2);

    monkeys.push_back(monkey);
}