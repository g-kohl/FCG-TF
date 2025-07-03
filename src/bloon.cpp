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

Bloon::Bloon(glm::vec3 translation, std::string modelName, int modelId)
    : translation(translation), modelName(modelName), modelId(modelId), level(1), time(0), blown(false) {}

bool Bloon::reachedEnd(){
    return translation.z > 6.5;
}

glm::vec3 Bloon::getTranslation(){
    return translation;
}

void Bloon::setTranslation(glm::vec4 deltaPosition){
    translation.x += deltaPosition.x;
    translation.z += deltaPosition.z;
}

std::string Bloon::getModelName(){
    return modelName;
}

int Bloon::getLevel(){
    return level;
}

int Bloon::getModelId(){
    return modelId;
}

float Bloon::getTime(){
    return time;
}

void Bloon::resetTime(){
    time = 0;
}

void Bloon::updateTime(float deltaTime){
    time += deltaTime;
}

bool Bloon::isBlown(){
    return blown;
}

void Bloon::blow(){
    blown = true;
}

void setupLevel(int level){
    glm::vec3 translationVector = glm::vec3(-8.0f, 1.0f, -2.0f);

    for(int i=0; i<level; i++){
        Bloon bloon = Bloon(
        translationVector,
        "bloon", 1);

        bloons.push_back(bloon);
    }
}

void updateBloons(float deltaTime){
    for(int i=0; i<int(bloons.size()); i++){
        bloons[i].updateTime(deltaTime);

        glm::vec4 nextPosition = bezier_spline(points, bloons[i].getTime());
        glm::vec3 translationVector = bloons[i].getTranslation();
        glm::vec4 bloonPosition = glm::vec4(translationVector.x, translationVector.y, translationVector.z, 0.0f);
        glm::vec4 deltaPosition = nextPosition - bloonPosition;
        
        bloons[i].setTranslation(deltaPosition);
    }
}