#include "camera.hpp"

Camera::Camera(float theta, float phi, float distance){
    free = false;
    this->theta = theta;
    this->phi = phi;
    this->distance = distance;

    x = distance*cos(phi)*sin(theta);
    y = distance*sin(phi);
    z = distance*cos(phi)*cos(theta);

    speed = 0.5f;
    position = glm::vec4(x,y,z,1.0f);

    lookat = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    view_vector = lookat - position;
    up_vector = glm::vec4(0.0f,1.0f,0.0f,0.0f);
    w_vector = -view_vector;
    w_vector /= norm(w_vector);
    u_vector = crossproduct(up_vector, w_vector);
    u_vector /= norm(u_vector);
}

void Camera::changeMode(){
    if(free)
        lookat = view_vector + glm::vec4(0.0f,0.0f,0.0f,1.0f); // erro está aqui

    free = !free;
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
    x = distance*cos(phi)*sin(theta);
    y = distance*sin(phi);
    z = distance*cos(phi)*cos(theta);

    if(free){
        view_vector = glm::vec4(x,-y,z,0.0f);
    }
    else{
        position = glm::vec4(x,y,z,1.0f);
        view_vector = lookat - position;
    }

    w_vector = -view_vector;
    w_vector /= norm(w_vector);
    u_vector = crossproduct(up_vector, w_vector);
    u_vector /= norm(u_vector);
}