#include "camera.hpp"

// constructor
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

// free

bool Camera::getMode(){
    return free;
}

void Camera::setMode(bool mode){
    free = mode;
}

// position

glm::vec4 Camera::getPosition(){
    return position;
}

void Camera::move(char direction, float deltaTime, std::vector<Monkey> &monkeys){
    if(!free)
        return;

    glm::vec4 nextPosition; 

    switch(direction) {
        case 'F':
            nextPosition = position + (-wVector * speed * deltaTime);
            if(!checkBboxCollisions(nextPosition, monkeys)){
                if(nextPosition.y >= 0.5f)
                    position = nextPosition;
            }

            break;
        case 'L':
            nextPosition = position + (-uVector * speed * deltaTime);
            if(!checkBboxCollisions(nextPosition, monkeys))
                position = nextPosition;

            break;
        case 'B':
            nextPosition = position + (wVector * speed * deltaTime);
            if(!checkBboxCollisions(nextPosition, monkeys)){
                if(nextPosition.y >= 0.5f)
                    position = nextPosition;
            }

            break;
        case 'R':
            nextPosition = position + (uVector * speed * deltaTime);
            if(!checkBboxCollisions(nextPosition, monkeys))
                position = nextPosition;

            break;
        case 'U':
            nextPosition = position + (upVector * speed * deltaTime);
            if(!checkBboxCollisions(nextPosition, monkeys))
                position = nextPosition;

            break;
        case 'D':
            nextPosition = position + (-upVector * speed * deltaTime);
            if(!checkBboxCollisions(nextPosition, monkeys)){
                if(nextPosition.y >= 0.5f)
                    position = nextPosition;
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
    distance = 11.0f;
    free = false;
    lookat = glm::vec4(0.0f,0.0f,0.0f,1.0f);
}

// view vector

glm::vec4 Camera::getViewVector(){
    return viewVector;
}

// up vector

glm::vec4 Camera::getUpVector(){
    return upVector;
}

void Camera::computeVectors(){
    viewVector = lookat - position;
    wVector = -viewVector;
    wVector /= norm(wVector);
    uVector = crossproduct(upVector, wVector);
    uVector /= norm(uVector);
}

bool Camera::checkBboxCollisions(glm::vec4 nextPosition, std::vector<Monkey> &monkeys){
    for(int j = 0; j < int(monkeys.size()); j++){        
        if(is_sphere_hit_bbox(monkeys[j].getMinBbox(), monkeys[j].getMaxBbox(), nextPosition, 0.1f))
            return true;
    }

    return false;
}