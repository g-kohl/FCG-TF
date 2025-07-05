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

Bloon::Bloon(glm::vec4 translation, std::string modelName, int modelId, int level, float time)
    : translation(translation), modelName(modelName), modelId(modelId), level(level), time(time), ready(false), blown(false) {

        SceneObject object = g_VirtualScene[modelName];
        bbox_max = glm::vec4(object.bbox_max.x, object.bbox_max.y, object.bbox_max.z, 1.0f);
        bbox_min = glm::vec4(object.bbox_min.x, object.bbox_min.y, object.bbox_min.z, 1.0f);
    }

bool Bloon::reachedEnd(){
    return translation.z > 6.5;
}

glm::vec4 Bloon::getTranslation(){
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

bool Bloon::isReady(){
    return ready;
}

void Bloon::setReady(){
    ready = true;
}

bool Bloon::isBlown(){
    return blown;
}

void Bloon::blow(){
    blown = true;
}

glm::vec4 Bloon::getMaxBbox(){
    return bbox_max;
}

glm::vec4 Bloon::getMinBbox(){
    return bbox_min;
}

void setupRound(int round){
    glm::vec4 translationVector = glm::vec4(-8.0f, 1.0f, -2.0f, 0.0f);

    for(int i=0; i<round*5; i++){
        int level = floor(i/5) + 1;
        level = std::min(level, MAX_LEVEL);

        Bloon bloon = Bloon(
        translationVector,
        "bloon", 1, level, -1.0*(i+5));

        bloons.push_back(bloon);
    }
}

void updateBloons(float deltaTime){
    for(int i=0; i<int(bloons.size()); i++){
        bloons[i].updateTime(deltaTime);

        if(bloons[i].getTime() >= 0)
            bloons[i].setReady();

        if(bloons[i].isReady()){
            glm::vec4 nextPosition = bezier_spline(points, bloons[i].getTime());
            glm::vec4 translationVector = bloons[i].getTranslation();
            glm::vec4 bloonPosition = glm::vec4(translationVector.x, translationVector.y, translationVector.z, 0.0f);
            glm::vec4 deltaPosition = nextPosition - bloonPosition;
            
            bloons[i].setTranslation(deltaPosition);
        }
    }
}