#include "bloon.hpp"

// list of bloons
std::vector<Bloon> bloons;

// control points
std::vector<glm::vec4> points = {
    glm::vec4(-9.2f, 0.0f, -1.0f, 1.0f),  
    glm::vec4(-8.0f, 0.0f, -1.0f, 1.0f),
    glm::vec4(-6.8f, 0.0f, -1.0f, 1.0f),

    glm::vec4(-5.6f, 0.0f, -1.0f, 1.0f),  
    glm::vec4(-4.4f, 0.0f, -1.0f, 1.0f),
    glm::vec4(-3.2f, 0.0f, -1.0f, 1.0f),

    glm::vec4(-2.0f, 0.0f, -1.0f, 1.0f),
    glm::vec4(-1.0f, 0.0f, -1.0f, 1.0f),
    glm::vec4(-0.05, 0.0f, -1.5f, 1.0f),

    glm::vec4(-0.05f, 0.0f, -2.5f, 1.0f),
    glm::vec4(-0.05f, 0.0f, -3.5f, 1.0f),
    glm::vec4(-0.8f, 0.0f, -4.0f, 1.0f),

    glm::vec4(-1.8f, 0.0f, -4.0f, 1.0f),
    glm::vec4(-2.8f, 0.0f, -4.0f, 1.0f),
    glm::vec4(-3.4f, 0.0f, -3.8f, 1.0f),

    glm::vec4(-3.4f, 0.0f, -2.8f, 1.0f),
    glm::vec4(-3.4f, 0.0f, -1.87f, 1.0f),
	glm::vec4(-3.4f, 0.0f, -0.93f, 1.0f),

    glm::vec4(-3.4f, 0.0f, 0.0f, 1.0f), 
	glm::vec4(-3.4f, 0.0f, 0.83f, 1.0f),
    glm::vec4(-3.4f, 0.0f, 1.67f, 1.0f),

    glm::vec4(-3.4f, 0.0f, 2.5f, 1.0f),
    glm::vec4(-3.4f, 0.0f, 3.5f, 1.0f),
 	glm::vec4(-4.2f, 0.0f, 4.0f, 1.0f),

    glm::vec4(-5.2f, 0.0f, 4.0f, 1.0f),
    glm::vec4(-6.2f, 0.0f, 4.0f, 1.0f),
    glm::vec4(-6.8f, 0.0f, 3.5f, 1.0f),

    glm::vec4(-6.8f, 0.0f, 2.5f, 1.0f), 
    glm::vec4(-6.8f, 0.0f, 1.5f, 1.0f),
	glm::vec4(-5.7f, 0.0f, 1.0f, 1.0f),

    glm::vec4(-4.7f, 0.0f, 1.0f, 1.0f),
    glm::vec4(-3.83f, 0.0f, 1.0f, 1.0f),
    glm::vec4(-2.96f, 0.0f, 1.0f, 1.0f),

    glm::vec4(-2.1f, 0.0f, 1.0f, 1.0f),
    glm::vec4(-1.23f, 0.0f, 1.0f, 1.0f),
    glm::vec4(-0.36f, 0.0f, 1.0f, 1.0f),

    glm::vec4(0.5f, 0.0f, 1.0f, 1.0f), 
    glm::vec4(1.5f, 0.0f, 1.0f, 1.0f),
	glm::vec4(2.8f, 0.0f, 0.0f, 1.0f),

    glm::vec4(2.8f, 0.0f, -1.0f, 1.0f), 
    glm::vec4(2.8f, 0.0f, -2.0f, 1.0f),
	glm::vec4(5.0f, 0.0f, -2.0f, 1.0f),

    glm::vec4(5.0f, 0.0f, -1.0f, 1.0f), 
	glm::vec4(5.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(5.0f, 0.0f, 1.0f, 1.0f),

    glm::vec4(5.0f, 0.0f, 2.0f, 1.0f),
    glm::vec4(5.0f, 0.0f, 3.0f, 1.0f),
	glm::vec4(2.0f, 0.0f, 3.0f, 1.0f),

    glm::vec4(1.0f, 0.0f, 3.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 3.0f, 1.0f),
    glm::vec4(-1.2f, 0.0f, 2.5f, 1.0f),
    glm::vec4(-1.2f, 0.0f, 6.5f, 1.0f),
};

// constructor
Bloon::Bloon(glm::vec4 translation, std::string modelName, int modelId, int level, float time)
    : translation(translation), modelName(modelName), modelId(modelId), level(level), time(time), ready(false), blown(false) {

        SceneObject object = g_VirtualScene[modelName];
        bbox_max = glm::vec4(object.bbox_max.x, object.bbox_max.y, object.bbox_max.z, 1.0f);
        bbox_min = glm::vec4(object.bbox_min.x, object.bbox_min.y, object.bbox_min.z, 1.0f);
    }


// translation

glm::vec4 Bloon::getTranslation(){
    return translation;
}

bool Bloon::reachedEnd(){
    return translation.z > MAX_MAP_HEIGHT;
}

void Bloon::setTranslation(glm::vec4 deltaPosition){
    translation.x += deltaPosition.x;
    translation.z += deltaPosition.z;
}

void Bloon::updateTranslation(float deltaTime){
    updateTime(deltaTime);

    if(getTime() >= 0)
        setReady();

    if(isReady()){
        glm::vec4 nextPosition = bezierSpline(points, getTime());
        glm::vec4 translationVector = getTranslation();
        glm::vec4 bloonPosition = glm::vec4(translationVector.x, translationVector.y, translationVector.z, 0.0f);
        glm::vec4 deltaPosition = nextPosition - bloonPosition;
        
        setTranslation(deltaPosition);
    }
}

// bounding box

glm::vec4 Bloon::getMaxBbox(){
    return bbox_max;
}

glm::vec4 Bloon::getMinBbox(){
    return bbox_min;
}

// model name

std::string Bloon::getModelName(){
    return modelName;
}

// model id

int Bloon::getModelId(){
    return modelId;
}

// level

int Bloon::getLevel(){
    return level;
}

void Bloon::loseLevel(int damage){
    level -= damage;

    if(level <= 0)
        blow();
}

// time

float Bloon::getTime(){
    return time;
}

void Bloon::updateTime(float deltaTime){
    time += deltaTime;
}

void Bloon::resetTime(){
    time = 0.0f;
}

// ready

bool Bloon::isReady(){
    return ready;
}

void Bloon::setReady(){
    ready = true;
}

// blown

bool Bloon::isBlown(){
    return blown;
}

void Bloon::blow(){
    blown = true;
}

void setupRound(int round){
    bloons.clear();
    glm::vec4 translationVector = INITIAL_POSITION;

    for(int i=0; i<round*5; i++){
        int level = floor(i/5) + 1;
        level = std::min(level, MAX_LEVEL);

        Bloon bloon = Bloon(
        translationVector,
        "bloon", BLOON_MODEL_ID, level, -1.0*(i+5));

        bloons.push_back(bloon);
    }
}

bool roundFinished(){
    for(int i=0; i<int(bloons.size()); i++){
        if(!bloons[i].isBlown())
            return false;
    }

    return true;
}