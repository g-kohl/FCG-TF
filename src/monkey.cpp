#include "monkey.hpp"

Monkey::Monkey(float t_x,float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, float r_y, float r_z, const char* name, int id){
    translation = glm::vec3(t_x, t_y, t_z);
    scaling = glm::vec3(s_x, s_y, s_z);
    rotation = glm::vec3(r_x, r_y, r_z);

    object_model_name = name;
    object_model_id = id;
    level = 1;
}