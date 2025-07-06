#include "camera.hpp"

Camera::Camera(float theta, float phi, float distance){
    free = false;

    float x = distance*cos(phi)*sin(theta);
    float y = distance*sin(phi);
    float z = distance*cos(phi)*cos(theta);

    speed = 10.0f;
    position = glm::vec4(x,y,z,1.0f);

    lookat = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    upVector = glm::vec4(0.0f,1.0f,0.0f,0.0f);

    computeVectors();
}

bool Camera::getMode(){
    return free;
}

void Camera::setMode(bool mode){
    free = mode;
}

glm::vec4 Camera::getPosition(){
    return position;
}

glm::vec4 Camera::getViewVector(){
    return viewVector;
}

glm::vec4 Camera::getUpVector(){
    return upVector;
}

void Camera::move(char direction, float delta_time, std::vector<Monkey> monkeys){
    if(!free)
        return;

    glm::vec4 nextPos; 

    switch(direction) {
        case 'F':
            nextPos = position + (-wVector * speed * delta_time);
            if(!checkBboxCollisions(nextPos, monkeys)){
                if(nextPos.y >= 0.5f)
                    position = nextPos;
            }

            break;
        case 'L':
            nextPos = position + (-uVector * speed * delta_time);
            if(!checkBboxCollisions(nextPos, monkeys))
                position = nextPos;

            break;
        case 'B':
            nextPos = position + (wVector * speed * delta_time);
            if(!checkBboxCollisions(nextPos, monkeys)){
                if(nextPos.y >= 0.5f)
                    position = nextPos;
            }

            break;
        case 'R':
            nextPos = position + (uVector * speed * delta_time);
            if(!checkBboxCollisions(nextPos, monkeys))
                position = nextPos;

            break;
        case 'U':
            nextPos = position + (upVector * speed * delta_time);
            if(!checkBboxCollisions(nextPos, monkeys))
                position = nextPos;

            break;
        case 'D':
            nextPos = position + (-upVector * speed * delta_time);
            if(!checkBboxCollisions(nextPos, monkeys)){
                if(nextPos.y >= 0.5f)
                    position = nextPos;
            }

            break;
        default:
            break;
    }
}

void Camera::update(float theta, float phi, float distance){
    if(free){
        float x = distance*cos(-phi)*sin(-theta)+position.x;
        float y = distance*sin(-phi)+position.y;
        float z = distance*cos(-phi)*cos(theta-M_PI)+position.z;

        lookat = glm::vec4(x,y,z,1.0f);
    }
    else{
        float x = distance*cos(phi)*sin(theta)+lookat.x;
        float y = distance*sin(phi)+lookat.y;
        float z = distance*cos(phi)*cos(theta)+lookat.z;

        position = glm::vec4(x,y,z,1.0f);
    }

    computeVectors();
}

void Camera::reset(float &theta, float &phi, float &distance){
    theta = 0.0f;
    phi = 3.141592f / 2.0f;
    distance = 10.0f;
    free = false;
    lookat = glm::vec4(0.0f,0.0f,0.0f,1.0f);
}

void Camera::computeVectors(){
    viewVector = lookat - position;
    wVector = -viewVector;
    wVector /= norm(wVector);
    uVector = crossproduct(upVector, wVector);
    uVector /= norm(uVector);
}

bool Camera::checkBboxCollisions(glm::vec4 nextPos, std::vector<Monkey> monkeys){

    for(int j = 0; j < int(monkeys.size()); j++){        
        if(is_sphere_hit_bbox(monkeys[j].getMinBbox(), monkeys[j].getMaxBbox(), nextPos, 0.1f))
            return true;
    }

    return false;
}