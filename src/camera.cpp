#include "camera.hpp"

Camera::Camera(float theta, float phi, float distance){
    free = false;

    float x = distance*cos(phi)*sin(theta);
    float y = distance*sin(phi);
    float z = distance*cos(phi)*cos(theta);

    speed = 10.0f;
    position = glm::vec4(x,y,z,1.0f);

    lookat = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    view_vector = lookat - position;
    up_vector = glm::vec4(0.0f,1.0f,0.0f,0.0f);
    w_vector = -view_vector;
    w_vector /= norm(w_vector);
    u_vector = crossproduct(up_vector, w_vector);
    u_vector /= norm(u_vector);
}

void Camera::move(char direction, float delta_time){
    if(!free)
        return;

    switch(direction) {
        case 'W':
            position += -w_vector * speed * delta_time;
            break;
        case 'A':
            position += -u_vector * speed * delta_time;
            break;
        case 'S':
            position += w_vector * speed * delta_time;
            break;
        case 'D':
            position += u_vector * speed * delta_time;
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

    view_vector = lookat - position;
    w_vector = -view_vector;
    w_vector /= norm(w_vector);
    u_vector = crossproduct(up_vector, w_vector);
    u_vector /= norm(u_vector);
}

void Camera::reset(float &theta, float &phi, float &distance){
    theta = 0.0f;
    phi = 3.141592f / 2.0f;
    distance = 15.0f;
    free = false;
    lookat = glm::vec4(0.0f,0.0f,0.0f,1.0f);
}
