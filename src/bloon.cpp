#include "bloon.hpp"

std::vector<Bloon> bloons;

std::vector<glm::vec4> points = {
        glm::vec4(-9.2f, 0.0f, -1.6f, 1.0f),  
        glm::vec4(-6.8f, 0.0f, -1.6f, 1.0f),
        glm::vec4(-4.4f, 0.0f, -1.6f, 1.0f),

        glm::vec4(-2.0f, 0.0f, -1.6f, 1.0f),
        glm::vec4(0.0f, 0.0f, -1.6f, 1.0f),
        glm::vec4(-0.05f, 0.0f, -3.0f, 1.0f),

        glm::vec4(-0.05f, 0.0f, -4.0f, 1.0f),
        glm::vec4(-0.05f, 0.0f, -5.0f, 1.0f),
        glm::vec4(-0.8f, 0.0f, -6.3f, 1.0f),

        glm::vec4(-1.8f, 0.0f, -6.3f, 1.0f),
        glm::vec4(-2.8f, 0.0f, -6.3f, 1.0f),
        glm::vec4(-3.5f, 0.0f, -5.2f, 1.0f),

        glm::vec4(-3.5f, 0.0f, -4.2f, 1.0f),
        glm::vec4(-3.5f, 0.0f, -2.8f, 1.0f),
        glm::vec4(-3.5f, 0.0f, -1.4f, 1.0f),

        glm::vec4(-3.5f, 0.0f, 0.0f, 1.0f),
        glm::vec4(-3.5f, 0.0f, 1.3f, 1.0f),
        glm::vec4(-3.5f, 0.0f, 2.6f, 1.0f),

        glm::vec4(-3.5f, 0.0f, 3.9f, 1.0f),
        glm::vec4(-3.5f, 0.0f, 4.9f, 1.0f),
        glm::vec4(-4.1f, 0.0f, 6.1f, 1.0f),

        glm::vec4(-5.1f, 0.0f, 6.1f, 1.0f),
        glm::vec4(-6.1f, 0.0f, 6.1f, 1.0f),
        glm::vec4(-6.8f, 0.0f, 4.9f, 1.0f),

        glm::vec4(-6.8f, 0.0f, 3.9f, 1.0f),
        glm::vec4(-6.8f, 0.0f, 2.9f, 1.0f),
        glm::vec4(-5.7f, 0.0f, 1.5f, 1.0f),

        glm::vec4(-4.7f, 0.0f, 1.5f, 1.0f),
        glm::vec4(-2.97f, 0.0f, 1.5f, 1.0f),
        glm::vec4(-1.24f, 0.0f, 1.5f, 1.0f),

        glm::vec4(0.5f, 0.0f, 1.5f, 1.0f),
        glm::vec4(1.5f, 0.0f, 1.5f, 1.0f),
        glm::vec4(2.8f, 0.0f, -0.3f, 1.0f),

        glm::vec4(2.8f, 0.0f, -1.3f, 1.0f),
        glm::vec4(2.8f, 0.0f, -3.3f, 1.0f),
        glm::vec4(5.0f, 0.0f, -3.3f, 1.0f),

        glm::vec4(5.0f, 0.0f, -1.3f, 1.0f),
        glm::vec4(5.0f, 0.0f, 0.14f, 1.0f),
        glm::vec4(5.0f, 0.0f, 1.57f, 1.0f),

        glm::vec4(5.0f, 0.0f, 3.0f, 1.0f),
        glm::vec4(5.0f, 0.0f, 3.83f, 1.0f),
        glm::vec4(2.8f, 0.0f, 4.5f, 1.0f),

        glm::vec4(0.1f, 0.0f, 4.5f, 1.0f),
        glm::vec4(-1.1f, 0.0f, 4.5f, 1.0f),
        glm::vec4(-1.2f, 0.0f, 8.5f, 1.0f),
        glm::vec4(-1.2f, 0.0f, 9.5f, 1.0f),
    };

Bloon::Bloon(float t_x,float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, float r_y, float r_z, const char* name, int id){
    translation = glm::vec3(t_x, t_y, t_z);
    scaling = glm::vec3(s_x, s_y, s_z);
    rotation = glm::vec3(r_x, r_y, r_z);

    object_model_name = name;
    object_model_id = id;
    level = 1;

    time = 0;
}

bool Bloon::reachedEnd(){
    if(translation.z > 6.44)
        return true;

    return false;
}

void setupLevel(int level){
    for(int i=0; i<level; i++){
        Bloon bloon = Bloon(
        -8.0f, 1.0f, -2.0f,
        0.3f, 0.3f, 0.3f,
        0.0f, 0.0f, 0.0f,
        "bloon", 1);

        bloons.push_back(bloon);
    }
}

void updateBloons(float deltaTime){
    for(int i=0; i<int(bloons.size()); i++){
        bloons[i].time += deltaTime;

        glm::vec4 d = bezier_spline(points, bloons[i].time);
        glm::vec4 bloonPosition = glm::vec4(bloons[i].translation.x, bloons[i].translation.y, bloons[i].translation.z, 0.0f);
        glm::vec4 v = d - bloonPosition;
        
        bloons[i].translation.x += v.x;
        bloons[i].translation.z += v.z;
    }
}